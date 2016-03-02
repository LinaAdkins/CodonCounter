#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect up our controls
    mFileSelectButton = this->findChild<QPushButton*>("btnFileSelect");
    connect( mFileSelectButton , SIGNAL(released()) , this , SLOT(HandleFileSelectBtn()) );
    mPathLineEdit = this->findChild<QLineEdit*>("lnFilePath");
    mPlotCodons = this->findChild<QCustomPlot*>("plotCodons");
    this->SetupGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleFileSelectBtn()
{
    fileName = QFileDialog::getOpenFileName( this ,
                                             tr("Open File") ,
                                             "/home" ,
                                             tr("Fasta (*.fas; *.fasta);;All files (*.*)")
                                            );
    mPathLineEdit->setText(fileName);

    LoadSequences(fileName);

    this->BindGraphToSequence(mSequenceList[0] );
}


/// Load all sequences from file
void MainWindow::LoadSequences( QString fileName ){

    QFile f( fileName );

    // Attempt to open file, display error and RETURN if unsucessful
    QString errMsg;
    QFileDevice::FileError err = QFileDevice::NoError;
    if( !f.open(QIODevice::ReadOnly)){
        errMsg = f.errorString();
        err = f.error();
        QMessageBox::information( NULL , errMsg , "Error!" );
        return;
    }

    Sequence currSequence;
    QString currTitle = "";

    // Loop through file
    QTextStream in(&f);
    while( !in.atEnd() ){
        QString line = in.readLine();

        if( line.length() != 0 )
        {

            // This line is a title
            if( line.contains(">") ){
                currTitle = line;
            }
            else // This line must be a sequence
            {
                currSequence = Sequence( currTitle , line );
                mSequenceList.append( currSequence );
            }
        }
    }

    f.close();
}

/// Set up initial styling for plot
void MainWindow::SetupGraph(){

    // Set up our plot
    QCPBars* numCodons = new QCPBars( mPlotCodons->xAxis , mPlotCodons->yAxis );
    mPlotCodons->addPlottable(numCodons);

    // Setup xAxis
    mPlotCodons->xAxis->setAutoTicks(false);
    mPlotCodons->xAxis->setAutoTickLabels(false);
    mPlotCodons->xAxis->setTickLabelRotation(60);
    mPlotCodons->xAxis->setSubTickCount(0);
    mPlotCodons->xAxis->setTickLength(0,4);
    mPlotCodons->xAxis->grid()->setVisible(true);

    // Interactions
    mPlotCodons->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
}

/// Bind our graph to a sequence
void MainWindow::BindGraphToSequence( Sequence s ){

    // Grab our plottable from setup, we only have one so use that
    QCPBars* numCodons = (QCPBars*)mPlotCodons->plottable(0);

    // Get our data to bind
    QVector<double> ticks;
    QVector<QString> labels;
    QVector<double> data;

    int iter = 1;
    for(auto e : s.mCodonOccurrences.keys())
    {
        ticks << iter;
        labels << e;
        data << s.mCodonOccurrences.value(e);

        iter++;
    }

    // Set up our xaxis labels
    mPlotCodons->xAxis->setTickVector(ticks);
    mPlotCodons->xAxis->setTickVectorLabels(labels);
    mPlotCodons->xAxis->setRange(0, labels.length());

    // Bind our data
    numCodons->setData( ticks , data );

    // Refresh
    mPlotCodons->rescaleAxes();
    mPlotCodons->replot();
}

