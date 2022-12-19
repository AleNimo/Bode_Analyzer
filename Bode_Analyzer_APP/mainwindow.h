#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Filter.h"

#include <QLayout>
#include <QList>
#include "qcustomplot.h"

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
    void on_Connect_USB_clicked();

    void on_Receive_USB_clicked();

    void on_Reset_Axis_clicked();

private:
    Ui::MainWindow *ui;

    QCPAxisRect *magAxisRect;
    QCPAxisRect *phaseAxisRect;

    QList<Filter*> filters;


};
#endif // MAINWINDOW_H
