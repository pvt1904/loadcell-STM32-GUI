#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QtCharts>
#include <QLineSeries>

#define lcdUpdateTime 100
#define cmdResponseTime 1000
#define bufferSize 10

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:   
    void on_pushButtonSend_1_clicked();

    void readData();

    void on_pushButtonOpen_clicked();

    void on_pushButtonLCConnect_clicked();

    void on_pushButtonLCOnOff_clicked();

    void on_pushButtonLCRead_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_pushButtonLCTare_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QTimer *connectionTimer;
    QTimer *checkResponseTimer;
    QTimer *portsHandleTimer;
    QString responseBuffer;
    QLineSeries *series;
    QTimer *graphTimerHandler;
    QChart *chart;
    QString currentHeader;
    double valuetestarray[bufferSize] = {0.0};
    bool tareFlag = false;
    void loadPorts();
    void loadBaudRate();
    void loadDataSize();
    void loadParity();
    void loadStopBits();
    void loadFlowControl();
    void writeToScreen(const QString& text, const QString& color);
    void setSerialConfigEnable(bool enable);
    void handleSerialError();
    bool validateHexString(const QString& hexString);
    QByteArray convertHexStringToAscii(const QString& hexString);
    void sendCommand(const QString& header, const QString& data);
    void checkResponse(const QString& header);
    void connectionHandler();
    void setupGraph();
    void updateGraph(double value);
};
#endif // MAINWINDOW_H
