#include "analogclockwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWindow *view = new AnalogClockWindow();
    QWidget *container = QWidget::createWindowContainer(view);
    container->setParent(ui->centralwidget);
    container->setMaximumSize(ui->centralwidget->size());
}


MainWindow::~MainWindow()
{
    delete ui;
}

