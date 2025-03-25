/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Home;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBoxBaudRate;
    QComboBox *comboBoxDatasize;
    QComboBox *comboBoxParity;
    QComboBox *comboBoxStopBits;
    QComboBox *comboBoxFlowControl;
    QPushButton *pushButtonOpen;
    QComboBox *comboBoxPort;
    QGroupBox *groupBox_2;
    QTextBrowser *textScreen;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEditSend;
    QCheckBox *checkBoxHex;
    QLineEdit *lineEditSend_2;
    QCheckBox *checkBoxHex_2;
    QPushButton *pushButtonSend_2;
    QLineEdit *lineEditSend_3;
    QCheckBox *checkBoxHex_3;
    QPushButton *pushButtonSend_3;
    QPushButton *pushButtonSend_1;
    QGroupBox *groupBox_3;
    QPushButton *pushButtonLCConnect;
    QLabel *labelLCStatus;
    QLabel *label_9;
    QPushButton *pushButtonLCRead;
    QLabel *label_11;
    QLCDNumber *lcdNumberWeigth;
    QPushButton *pushButtonLCTare;
    QPushButton *pushButtonLCOnOff;
    QSpinBox *spinBoxWeight;
    QWidget *Graph;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(772, 660);
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 10, 751, 591));
        Home = new QWidget();
        Home->setObjectName("Home");
        groupBox = new QGroupBox(Home);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 161, 401));
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 81, 21));
        label->setFont(font);
        label->setTextFormat(Qt::TextFormat::AutoText);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 80, 81, 21));
        label_2->setFont(font);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 130, 81, 21));
        label_3->setFont(font);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 180, 81, 21));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 230, 91, 21));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 280, 121, 21));
        label_6->setFont(font);
        comboBoxBaudRate = new QComboBox(groupBox);
        comboBoxBaudRate->setObjectName("comboBoxBaudRate");
        comboBoxBaudRate->setGeometry(QRect(20, 100, 121, 22));
        comboBoxBaudRate->setFont(font);
        comboBoxBaudRate->setEditable(false);
        comboBoxDatasize = new QComboBox(groupBox);
        comboBoxDatasize->setObjectName("comboBoxDatasize");
        comboBoxDatasize->setGeometry(QRect(20, 150, 121, 22));
        comboBoxDatasize->setFont(font);
        comboBoxDatasize->setEditable(false);
        comboBoxParity = new QComboBox(groupBox);
        comboBoxParity->setObjectName("comboBoxParity");
        comboBoxParity->setGeometry(QRect(20, 200, 121, 22));
        comboBoxParity->setFont(font);
        comboBoxParity->setEditable(false);
        comboBoxStopBits = new QComboBox(groupBox);
        comboBoxStopBits->setObjectName("comboBoxStopBits");
        comboBoxStopBits->setGeometry(QRect(20, 250, 121, 22));
        comboBoxStopBits->setFont(font);
        comboBoxStopBits->setEditable(false);
        comboBoxFlowControl = new QComboBox(groupBox);
        comboBoxFlowControl->setObjectName("comboBoxFlowControl");
        comboBoxFlowControl->setGeometry(QRect(20, 300, 121, 22));
        comboBoxFlowControl->setFont(font);
        comboBoxFlowControl->setEditable(false);
        pushButtonOpen = new QPushButton(groupBox);
        pushButtonOpen->setObjectName("pushButtonOpen");
        pushButtonOpen->setGeometry(QRect(20, 350, 121, 22));
        pushButtonOpen->setFont(font);
        comboBoxPort = new QComboBox(groupBox);
        comboBoxPort->setObjectName("comboBoxPort");
        comboBoxPort->setEnabled(true);
        comboBoxPort->setGeometry(QRect(20, 50, 121, 22));
        comboBoxPort->setFont(font);
        comboBoxPort->setEditable(false);
        groupBox_2 = new QGroupBox(Home);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(200, 10, 531, 401));
        groupBox_2->setFont(font);
        textScreen = new QTextBrowser(groupBox_2);
        textScreen->setObjectName("textScreen");
        textScreen->setGeometry(QRect(20, 50, 491, 221));
        textScreen->setMouseTracking(false);
        textScreen->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);
        textScreen->setPlaceholderText(QString::fromUtf8(""));
        textScreen->setSearchPaths(QStringList{});
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 30, 141, 16));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 280, 111, 16));
        lineEditSend = new QLineEdit(groupBox_2);
        lineEditSend->setObjectName("lineEditSend");
        lineEditSend->setGeometry(QRect(20, 300, 281, 22));
        checkBoxHex = new QCheckBox(groupBox_2);
        checkBoxHex->setObjectName("checkBoxHex");
        checkBoxHex->setGeometry(QRect(340, 300, 61, 22));
        QFont font1;
        font1.setPointSize(12);
        checkBoxHex->setFont(font1);
        lineEditSend_2 = new QLineEdit(groupBox_2);
        lineEditSend_2->setObjectName("lineEditSend_2");
        lineEditSend_2->setGeometry(QRect(20, 330, 281, 22));
        checkBoxHex_2 = new QCheckBox(groupBox_2);
        checkBoxHex_2->setObjectName("checkBoxHex_2");
        checkBoxHex_2->setGeometry(QRect(340, 330, 61, 22));
        checkBoxHex_2->setFont(font1);
        pushButtonSend_2 = new QPushButton(groupBox_2);
        pushButtonSend_2->setObjectName("pushButtonSend_2");
        pushButtonSend_2->setGeometry(QRect(430, 330, 81, 22));
        pushButtonSend_2->setFont(font1);
        lineEditSend_3 = new QLineEdit(groupBox_2);
        lineEditSend_3->setObjectName("lineEditSend_3");
        lineEditSend_3->setGeometry(QRect(20, 360, 281, 22));
        checkBoxHex_3 = new QCheckBox(groupBox_2);
        checkBoxHex_3->setObjectName("checkBoxHex_3");
        checkBoxHex_3->setGeometry(QRect(340, 360, 61, 22));
        checkBoxHex_3->setFont(font1);
        pushButtonSend_3 = new QPushButton(groupBox_2);
        pushButtonSend_3->setObjectName("pushButtonSend_3");
        pushButtonSend_3->setGeometry(QRect(430, 360, 81, 22));
        pushButtonSend_3->setFont(font1);
        pushButtonSend_1 = new QPushButton(groupBox_2);
        pushButtonSend_1->setObjectName("pushButtonSend_1");
        pushButtonSend_1->setGeometry(QRect(430, 300, 81, 22));
        pushButtonSend_1->setFont(font1);
        groupBox_3 = new QGroupBox(Home);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 420, 721, 141));
        groupBox_3->setFont(font1);
        pushButtonLCConnect = new QPushButton(groupBox_3);
        pushButtonLCConnect->setObjectName("pushButtonLCConnect");
        pushButtonLCConnect->setGeometry(QRect(30, 60, 121, 22));
        pushButtonLCConnect->setFont(font);
        labelLCStatus = new QLabel(groupBox_3);
        labelLCStatus->setObjectName("labelLCStatus");
        labelLCStatus->setGeometry(QRect(30, 90, 121, 21));
        labelLCStatus->setFont(font);
        labelLCStatus->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 30, 121, 21));
        label_9->setFont(font);
        pushButtonLCRead = new QPushButton(groupBox_3);
        pushButtonLCRead->setObjectName("pushButtonLCRead");
        pushButtonLCRead->setEnabled(false);
        pushButtonLCRead->setGeometry(QRect(259, 60, 121, 22));
        pushButtonLCRead->setFont(font);
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(249, 30, 121, 21));
        label_11->setFont(font);
        lcdNumberWeigth = new QLCDNumber(groupBox_3);
        lcdNumberWeigth->setObjectName("lcdNumberWeigth");
        lcdNumberWeigth->setEnabled(false);
        lcdNumberWeigth->setGeometry(QRect(490, 30, 131, 41));
        lcdNumberWeigth->setSmallDecimalPoint(false);
        lcdNumberWeigth->setProperty("value", QVariant(0.000000000000000));
        lcdNumberWeigth->setProperty("intValue", QVariant(0));
        pushButtonLCTare = new QPushButton(groupBox_3);
        pushButtonLCTare->setObjectName("pushButtonLCTare");
        pushButtonLCTare->setEnabled(false);
        pushButtonLCTare->setGeometry(QRect(490, 80, 41, 31));
        pushButtonLCTare->setFont(font);
        pushButtonLCOnOff = new QPushButton(groupBox_3);
        pushButtonLCOnOff->setObjectName("pushButtonLCOnOff");
        pushButtonLCOnOff->setGeometry(QRect(580, 80, 41, 31));
        pushButtonLCOnOff->setFont(font);
        spinBoxWeight = new QSpinBox(groupBox_3);
        spinBoxWeight->setObjectName("spinBoxWeight");
        spinBoxWeight->setGeometry(QRect(260, 90, 121, 31));
        spinBoxWeight->setMaximum(5000);
        tabWidget->addTab(Home, QString());
        Graph = new QWidget();
        Graph->setObjectName("Graph");
        tabWidget->addTab(Graph, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 772, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "UART Communication", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "UART configuration", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Port name</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Baud rate</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Data size</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Parity</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Stop bits</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Flow control</span></p></body></html>", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "UART test", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Received/Sent data", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        checkBoxHex->setText(QCoreApplication::translate("MainWindow", "HEX", nullptr));
        checkBoxHex_2->setText(QCoreApplication::translate("MainWindow", "HEX", nullptr));
        pushButtonSend_2->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        checkBoxHex_3->setText(QCoreApplication::translate("MainWindow", "HEX", nullptr));
        pushButtonSend_3->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        pushButtonSend_1->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Load cell", nullptr));
        pushButtonLCConnect->setText(QCoreApplication::translate("MainWindow", "Check", nullptr));
        labelLCStatus->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Disconnected</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Connection</span></p></body></html>", nullptr));
        pushButtonLCRead->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Calibration</span></p></body></html>", nullptr));
        pushButtonLCTare->setText(QCoreApplication::translate("MainWindow", "TARE", nullptr));
        pushButtonLCOnOff->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Home), QCoreApplication::translate("MainWindow", "Home", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Graph), QCoreApplication::translate("MainWindow", "Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
