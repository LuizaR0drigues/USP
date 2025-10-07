/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *home;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTextBrowser *textBrowser;
    QWidget *painter;
    QPushButton *button_apagar;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QLabel *myFrame;
    QTextBrowser *textBrowser_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(808, 407);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-10, 0, 801, 361));
        home = new QWidget();
        home->setObjectName("home");
        layoutWidget = new QWidget(home);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(340, 150, 96, 60));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout_2->addWidget(pushButton_4);

        textBrowser = new QTextBrowser(home);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(220, 100, 331, 51));
        stackedWidget->addWidget(home);
        painter = new QWidget();
        painter->setObjectName("painter");
        button_apagar = new QPushButton(painter);
        button_apagar->setObjectName("button_apagar");
        button_apagar->setGeometry(QRect(20, 150, 80, 26));
        toolButton = new QToolButton(painter);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(30, 60, 23, 21));
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color:orange;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        toolButton_2 = new QToolButton(painter);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(60, 60, 23, 21));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: yellow;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        toolButton_3 = new QToolButton(painter);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setGeometry(QRect(30, 90, 23, 21));
        toolButton_3->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: blue;\n"
" \n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        toolButton_4 = new QToolButton(painter);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setGeometry(QRect(60, 90, 21, 21));
        toolButton_4->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: red;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        toolButton_5 = new QToolButton(painter);
        toolButton_5->setObjectName("toolButton_5");
        toolButton_5->setGeometry(QRect(30, 120, 23, 21));
        toolButton_5->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: green;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        toolButton_6 = new QToolButton(painter);
        toolButton_6->setObjectName("toolButton_6");
        toolButton_6->setGeometry(QRect(60, 120, 23, 21));
        toolButton_6->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: black;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        myFrame = new QLabel(painter);
        myFrame->setObjectName("myFrame");
        myFrame->setGeometry(QRect(110, 40, 681, 341));
        myFrame->setMaximumSize(QSize(800, 800));
        textBrowser_2 = new QTextBrowser(painter);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(30, 30, 61, 31));
        stackedWidget->addWidget(painter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 808, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#c64600;\">PoL\302\262igono</span></p></body></html>", nullptr));
        button_apagar->setText(QCoreApplication::translate("MainWindow", "Apagar", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_5->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        myFrame->setText(QString());
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Cores</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
