#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect up our controls
    mFileSelectButton = this->findChild<QPushButton*>("btnFileSelect");
    connect( mFileSelectButton , SIGNAL(released()) , this , SLOT(HandleFileSelectBtn()) );
    mPathLineEdit = this->findChild<QLineEdit*>("lnFilePath");
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

    for( Sequence& s : mSequenceList ){
        // Nothing yet
    }

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


