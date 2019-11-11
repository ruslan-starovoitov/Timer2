#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "analogclockwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startStopButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    AnalogClockWindow *view;
};
#endif // MAINWINDOW_H
