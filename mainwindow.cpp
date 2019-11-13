#include "analogclockwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new AnalogClockWindow();


    connect(view, SIGNAL(timeChanged(long long)), this, SLOT(DrawDigitalTime(long long)));


    QWidget *container = QWidget::createWindowContainer(view);
    container->setParent(ui->centralwidget);
    QSize size(500,500);
    container->setMaximumSize(size);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startStopButton_clicked()
{
    view->startStop();


    if(ui->startStopButton->text()=="Start"){
        ui->startStopButton->setText("Stop");
    }else{
        ui->startStopButton->setText("Start");
    }
}

void MainWindow::DrawDigitalTime(long long time){
    int minutes = ((time/1000000000)/60)%60;
    int seconds = (time/1000000000)%60;
    int milliseconds = (time/1000000)%1000;

    ui->lcdMinutes->display(minutes);
    ui->lcdSeconds->display(seconds);
    ui->lcdMilliseconds->display(milliseconds);
}


void MainWindow::on_resetButton_clicked()
{
    view->reset();
}
