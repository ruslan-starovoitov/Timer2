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

    QWidget *container = QWidget::createWindowContainer(view);
    container->setParent(ui->centralwidget);
    QSize size(500,500);
    container->setMaximumSize(size);

}

MainWindow::~MainWindow()
{
    delete ui;
}
