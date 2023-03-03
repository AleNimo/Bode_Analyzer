/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *PlotWidget;
    QPushButton *Receive_USB;
    QPushButton *Connect_USB;
    QLabel *label_connection_ok;
    QPushButton *Reset_Axis;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1212, 674);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(310, 30, 581, 491));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        PlotWidget = new QCustomPlot(verticalLayoutWidget);
        PlotWidget->setObjectName(QString::fromUtf8("PlotWidget"));

        verticalLayout->addWidget(PlotWidget);

        Receive_USB = new QPushButton(verticalLayoutWidget);
        Receive_USB->setObjectName(QString::fromUtf8("Receive_USB"));

        verticalLayout->addWidget(Receive_USB);

        Connect_USB = new QPushButton(verticalLayoutWidget);
        Connect_USB->setObjectName(QString::fromUtf8("Connect_USB"));

        verticalLayout->addWidget(Connect_USB);

        label_connection_ok = new QLabel(centralwidget);
        label_connection_ok->setObjectName(QString::fromUtf8("label_connection_ok"));
        label_connection_ok->setEnabled(true);
        label_connection_ok->setGeometry(QRect(420, 540, 361, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_connection_ok->setFont(font);
        label_connection_ok->setAlignment(Qt::AlignCenter);
        Reset_Axis = new QPushButton(centralwidget);
        Reset_Axis->setObjectName(QString::fromUtf8("Reset_Axis"));
        Reset_Axis->setGeometry(QRect(900, 30, 101, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1212, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Receive_USB->setText(QCoreApplication::translate("MainWindow", "Recibir Bode", nullptr));
        Connect_USB->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        label_connection_ok->setText(QCoreApplication::translate("MainWindow", "Conexi\303\263n Exitosa", nullptr));
        Reset_Axis->setText(QCoreApplication::translate("MainWindow", "Reestablecer Ejes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
