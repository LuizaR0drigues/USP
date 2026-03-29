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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
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
    QPushButton *BtnIniciar;
    QPushButton *BtnFechar;
    QTextBrowser *textBrowser;
    QWidget *painter;
    QToolButton *btnLaranjaAresta;
    QToolButton *btnAmareloAresta;
    QToolButton *btnAzulAresta;
    QToolButton *btnVermelhoAresta;
    QToolButton *btnVerdeAresta;
    QToolButton *btnPretoAresta;
    QLabel *myFrame;
    QTextBrowser *textBrowser_2;
    QToolButton *btnVermelhoPreen;
    QToolButton *btnPretoPreen;
    QToolButton *btnLaranjaPreen;
    QTextBrowser *textBrowser_3;
    QToolButton *btnVerdePreen;
    QPushButton *button_apagar;
    QToolButton *btnAzulPreen;
    QToolButton *btnAmareloPreen;
    QSpinBox *inputGrossura;
    QTextEdit *textEdit;
    QToolButton *btnBrancoAresta;
    QToolButton *btnBrancoPreen;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(969, 544);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-10, 0, 971, 541));
        home = new QWidget();
        home->setObjectName("home");
        layoutWidget = new QWidget(home);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(440, 250, 96, 60));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        BtnIniciar = new QPushButton(layoutWidget);
        BtnIniciar->setObjectName("BtnIniciar");

        verticalLayout_2->addWidget(BtnIniciar);

        BtnFechar = new QPushButton(layoutWidget);
        BtnFechar->setObjectName("BtnFechar");

        verticalLayout_2->addWidget(BtnFechar);

        textBrowser = new QTextBrowser(home);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(320, 200, 331, 51));
        stackedWidget->addWidget(home);
        painter = new QWidget();
        painter->setObjectName("painter");
        btnLaranjaAresta = new QToolButton(painter);
        btnLaranjaAresta->setObjectName("btnLaranjaAresta");
        btnLaranjaAresta->setGeometry(QRect(30, 60, 51, 21));
        btnLaranjaAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color:orange;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnAmareloAresta = new QToolButton(painter);
        btnAmareloAresta->setObjectName("btnAmareloAresta");
        btnAmareloAresta->setGeometry(QRect(100, 60, 51, 21));
        btnAmareloAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: yellow;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnAzulAresta = new QToolButton(painter);
        btnAzulAresta->setObjectName("btnAzulAresta");
        btnAzulAresta->setGeometry(QRect(30, 90, 51, 21));
        btnAzulAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: blue;\n"
" \n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnVermelhoAresta = new QToolButton(painter);
        btnVermelhoAresta->setObjectName("btnVermelhoAresta");
        btnVermelhoAresta->setGeometry(QRect(100, 90, 51, 21));
        btnVermelhoAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: red;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnVerdeAresta = new QToolButton(painter);
        btnVerdeAresta->setObjectName("btnVerdeAresta");
        btnVerdeAresta->setGeometry(QRect(30, 120, 51, 21));
        btnVerdeAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: green;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnPretoAresta = new QToolButton(painter);
        btnPretoAresta->setObjectName("btnPretoAresta");
        btnPretoAresta->setGeometry(QRect(100, 120, 51, 21));
        btnPretoAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: black;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        myFrame = new QLabel(painter);
        myFrame->setObjectName("myFrame");
        myFrame->setGeometry(QRect(228, 20, 720, 500));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(myFrame->sizePolicy().hasHeightForWidth());
        myFrame->setSizePolicy(sizePolicy);
        myFrame->setMaximumSize(QSize(800, 600));
        textBrowser_2 = new QTextBrowser(painter);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(20, 16, 141, 41));
        QFont font;
        font.setPointSize(9);
        textBrowser_2->setFont(font);
        textBrowser_2->setAutoFormatting(QTextEdit::AutoFormattingFlag::AutoNone);
        btnVermelhoPreen = new QToolButton(painter);
        btnVermelhoPreen->setObjectName("btnVermelhoPreen");
        btnVermelhoPreen->setGeometry(QRect(100, 260, 51, 21));
        btnVermelhoPreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: red;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnPretoPreen = new QToolButton(painter);
        btnPretoPreen->setObjectName("btnPretoPreen");
        btnPretoPreen->setGeometry(QRect(100, 290, 51, 21));
        btnPretoPreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: black;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnLaranjaPreen = new QToolButton(painter);
        btnLaranjaPreen->setObjectName("btnLaranjaPreen");
        btnLaranjaPreen->setGeometry(QRect(30, 230, 51, 21));
        btnLaranjaPreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color:orange;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        textBrowser_3 = new QTextBrowser(painter);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(20, 186, 141, 41));
        textBrowser_3->setFont(font);
        textBrowser_3->setAutoFormatting(QTextEdit::AutoFormattingFlag::AutoNone);
        btnVerdePreen = new QToolButton(painter);
        btnVerdePreen->setObjectName("btnVerdePreen");
        btnVerdePreen->setGeometry(QRect(30, 290, 51, 21));
        btnVerdePreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: green;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        button_apagar = new QPushButton(painter);
        button_apagar->setObjectName("button_apagar");
        button_apagar->setGeometry(QRect(40, 460, 111, 41));
        btnAzulPreen = new QToolButton(painter);
        btnAzulPreen->setObjectName("btnAzulPreen");
        btnAzulPreen->setGeometry(QRect(30, 260, 51, 21));
        btnAzulPreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: blue;\n"
" \n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        btnAmareloPreen = new QToolButton(painter);
        btnAmareloPreen->setObjectName("btnAmareloPreen");
        btnAmareloPreen->setGeometry(QRect(100, 230, 51, 21));
        btnAmareloPreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: yellow;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        inputGrossura = new QSpinBox(painter);
        inputGrossura->setObjectName("inputGrossura");
        inputGrossura->setGeometry(QRect(20, 410, 141, 31));
        inputGrossura->setMinimum(1);
        inputGrossura->setMaximum(10);
        textEdit = new QTextEdit(painter);
        textEdit->setObjectName("textEdit");
        textEdit->setEnabled(true);
        textEdit->setGeometry(QRect(20, 350, 141, 55));
        textEdit->setReadOnly(true);
        btnBrancoAresta = new QToolButton(painter);
        btnBrancoAresta->setObjectName("btnBrancoAresta");
        btnBrancoAresta->setGeometry(QRect(50, 150, 71, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        btnBrancoAresta->setPalette(palette);
        btnBrancoAresta->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: white;\n"
"	border-color: rgb(0, 0, 0);\n"
"    border-radius: 50px;\n"
"}\n"
""));
        btnBrancoPreen = new QToolButton(painter);
        btnBrancoPreen->setObjectName("btnBrancoPreen");
        btnBrancoPreen->setGeometry(QRect(50, 320, 71, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush1(QColor(255, 255, 255, 128));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush1);
#endif
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush1);
#endif
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush1);
#endif
        btnBrancoPreen->setPalette(palette1);
        btnBrancoPreen->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    background-color: white;\n"
"	border-color: rgb(0, 0, 0);\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        stackedWidget->addWidget(painter);
        MainWindow->setCentralWidget(centralwidget);
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
        BtnIniciar->setText(QCoreApplication::translate("MainWindow", "Iniciar", nullptr));
        BtnFechar->setText(QCoreApplication::translate("MainWindow", "Fechar", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu Sans'; font-size:20pt; font-weight:700; color:#c64600;\">PoL\302\262igono</span></p></body></html>", nullptr));
        btnLaranjaAresta->setText(QString());
        btnAmareloAresta->setText(QString());
        btnAzulAresta->setText(QString());
        btnVermelhoAresta->setText(QString());
        btnVerdeAresta->setText(QString());
        btnPretoAresta->setText(QString());
        myFrame->setText(QString());
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu Sans'; font-size:18pt; font-weight:700;\">Cor aresta</span></p></body></html>", nullptr));
        btnVermelhoPreen->setText(QString());
        btnPretoPreen->setText(QString());
        btnLaranjaPreen->setText(QString());
        textBrowser_3->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu Sans'; font-size:18pt; font-weight:700;\">Cor preen.</span></p></body></html>", nullptr));
        btnVerdePreen->setText(QString());
        button_apagar->setText(QCoreApplication::translate("MainWindow", "Apagar", nullptr));
        btnAzulPreen->setText(QString());
        btnAmareloPreen->setText(QString());
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:700;\">Grossura do contorno:</span></p></body></html>", nullptr));
        btnBrancoAresta->setText(QString());
        btnBrancoPreen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
