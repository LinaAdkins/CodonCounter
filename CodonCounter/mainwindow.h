#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QLineEdit>
#include <QMessageBox>
#include "qcustomplot.h"

#include "Sequence.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void HandleFileSelectBtn();
        void ComboUpdate( int );

    private:
        void LoadSequences( QString filename );
        void BindGraphToSequence( Sequence s );
        void SetupGraph();
        Ui::MainWindow *ui;
        QPushButton *mFileSelectButton;
        QString fileName = "";
        QLineEdit *mPathLineEdit;
        QList<Sequence> mSequenceList;
        QCustomPlot *mPlotCodons;
        QComboBox* mComboSequence;

};

#endif // MAINWINDOW_H
