#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new QSerialPort(this);

    portsHandleTimer = new QTimer(this);
    connect(portsHandleTimer, &QTimer::timeout, this, &MainWindow::loadPorts);
    portsHandleTimer->start(1000);

    connectionTimer = new QTimer(this);
    connect(connectionTimer, &QTimer::timeout, this, &MainWindow::connectionHandler);

    checkResponseTimer = new QTimer(this);

    loadPorts();
    loadBaudRate();
    loadDataSize();
    loadParity();
    loadStopBits();
    loadFlowControl();
    ui->doubleSpinBoxWeight->setSuffix(" g");

    //for the graph
    series = new QLineSeries(this);
    graphTimerHandler = new QTimer(this);
    setupGraph();

    ui->tabWidget->setCurrentIndex(0);
    ui->lcdNumberWeigth->display(0.0) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPorts(){
    if (ui->comboBoxPort->count() != QSerialPortInfo::availablePorts().count() && ui->pushButtonOpen->text() == "Open"){
        ui->comboBoxPort->clear();
        foreach (auto &port, QSerialPortInfo::availablePorts())
            ui->comboBoxPort->addItem(port.portName());
    }
}

void MainWindow::loadBaudRate(){
    ui->comboBoxBaudRate->addItem("1200", QSerialPort::Baud1200);
    ui->comboBoxBaudRate->addItem("2400", QSerialPort::Baud2400);
    ui->comboBoxBaudRate->addItem("4800", QSerialPort::Baud4800);
    ui->comboBoxBaudRate->addItem("9600", QSerialPort::Baud9600);
    ui->comboBoxBaudRate->addItem("19200", QSerialPort::Baud19200);
    ui->comboBoxBaudRate->addItem("38400", QSerialPort::Baud38400);
    ui->comboBoxBaudRate->addItem("57600", QSerialPort::Baud57600);
    ui->comboBoxBaudRate->addItem("115200", QSerialPort::Baud115200);
    ui->comboBoxBaudRate->setCurrentText("9600");
}

void MainWindow::loadDataSize(){
    ui->comboBoxDatasize->addItem("7");
    ui->comboBoxDatasize->addItem("8");
    ui->comboBoxDatasize->setCurrentIndex(1);
}

void MainWindow::loadParity(){
    ui->comboBoxParity->addItem("none");
    ui->comboBoxParity->addItem("even");
    ui->comboBoxParity->addItem("odd");
    ui->comboBoxParity->addItem("mark");
}

void MainWindow::loadStopBits(){
    ui->comboBoxStopBits->addItem("1");
    ui->comboBoxStopBits->addItem("1.5");
    ui->comboBoxStopBits->addItem("2");
}

void MainWindow::loadFlowControl(){
    ui->comboBoxFlowControl->addItem("none");
    ui->comboBoxFlowControl->addItem("Xon/Xoff");
    ui->comboBoxFlowControl->addItem("hardware");
}

void MainWindow::on_pushButtonOpen_clicked()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        ui->pushButtonOpen->setText("Open");
        ui->labelLCStatus->setText("Disconnected");
        connectionTimer->stop();
        ui->pushButtonLCRead->setEnabled(false);
        writeToScreen("Serial port " + serialPort->portName() + " closed\n","green");
        setSerialConfigEnable(true);
        disconnect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
        disconnect(serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleSerialError);
        return;
    }

    serialPort->setPortName(ui->comboBoxPort->currentText());
    serialPort->setBaudRate(ui->comboBoxBaudRate->currentData().toInt());
    serialPort->setDataBits(ui->comboBoxDatasize->currentText() == "7" ? QSerialPort::Data7 : QSerialPort::Data8);
    serialPort->setStopBits(ui->comboBoxStopBits->currentText() == "1" ? QSerialPort::OneStop :
                                ui->comboBoxStopBits->currentText() == "1.5" ? QSerialPort::OneAndHalfStop : QSerialPort::TwoStop);
    serialPort->setParity(ui->comboBoxParity->currentText() == "none" ? QSerialPort::NoParity :
                              ui->comboBoxParity->currentText() == "even" ? QSerialPort::EvenParity :
                              ui->comboBoxParity->currentText() == "odd" ? QSerialPort::OddParity : QSerialPort::MarkParity);
    serialPort->setFlowControl(ui->comboBoxFlowControl->currentText() == "none" ? QSerialPort::NoFlowControl :
                                   ui->comboBoxFlowControl->currentText() == "Xon/Xoff" ? QSerialPort::SoftwareControl : QSerialPort::HardwareControl);

    qDebug() << serialPort->portName();
    qDebug() << serialPort->baudRate();
    qDebug() << serialPort->dataBits();
    qDebug() << serialPort->stopBits();
    qDebug() << serialPort->parity();
    qDebug() << serialPort->flowControl();

    if (serialPort->open(QIODevice::ReadWrite)) {
        ui->pushButtonOpen->setText("Close");
        ui->labelLCStatus->setText("Disconnected");
        connectionTimer->stop();
        writeToScreen("Serial port " + serialPort->portName() + " opened\n","green");
        qDebug() << serialPort->isOpen();
        setSerialConfigEnable(false);
        connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
        connect(serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleSerialError);
    } else {
        QMessageBox::critical(this, "Error", serialPort->errorString());
    }
}

void MainWindow::on_pushButtonSend_1_clicked()
{
    if(!serialPort->isOpen()) {
        QMessageBox::warning(this, "Warning", "Serial port is not connected.");
        return;
    }

    if(!ui->checkBoxHex->checkState()){
        QString data = ui->lineEditSend->text();
        serialPort->write(data.toUtf8());
        writeToScreen(data, "red");
        return;
    }

    QString hexString = ui->lineEditSend->text();
    if (!validateHexString(hexString)) {
        QMessageBox::critical(this, "Error", "Invalid HEX format!");
        return;
    }

    QByteArray asciiData = convertHexStringToAscii(ui->lineEditSend->text());
    serialPort->write(asciiData);
    writeToScreen(asciiData, "red");
    return;
}

void MainWindow::readData(){
    if (!serialPort->isOpen()){
        QMessageBox::warning(this, "Warning", "Serial port is not connected.");
        return;
    }

    QByteArray data = serialPort->readAll();
    QString dataString = QString(data);
    responseBuffer += dataString;
    if (responseBuffer.length() == 11) {
        checkResponse(responseBuffer.left(4));
        disconnect(checkResponseTimer, &QTimer::timeout, nullptr, nullptr);
        checkResponseTimer->stop();
        responseBuffer.clear();
    }
    writeToScreen(dataString, "black");
}

void MainWindow::writeToScreen(const QString& text, const QString& color)
{
    QTextCharFormat format;
    format.setForeground(QColor(color));

    QTextCursor cursor(ui->textScreen->textCursor());
    cursor.setCharFormat(format);
    cursor.insertText(text);

    ui->textScreen->ensureCursorVisible();
}
void MainWindow::setSerialConfigEnable(bool enable){
    ui->comboBoxPort->setEnabled(enable);
    ui->comboBoxBaudRate->setEnabled(enable);
    ui->comboBoxDatasize->setEnabled(enable);
    ui->comboBoxParity->setEnabled(enable);
    ui->comboBoxStopBits->setEnabled(enable);
    ui->comboBoxFlowControl->setEnabled(enable);
    return;
}
void MainWindow::handleSerialError(){
    QMessageBox::critical(this, "Error", serialPort->errorString());
    serialPort->close();
    if (!serialPort->isOpen()){
        ui->pushButtonOpen->setText("Open");
        writeToScreen("Serial port " + serialPort->portName() + " closed\n","green");
        setSerialConfigEnable(true);
        disconnect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
        disconnect(serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleSerialError);
        ui->labelLCStatus->setText("Disconnected");
        connectionTimer->stop();
        return;
    }
}

bool MainWindow::validateHexString(const QString& hexString){
    QRegularExpression regex("^(?:[0-9A-Fa-f]{2}(?:\\s|$))*$");
    return regex.match(hexString).hasMatch();
}

QByteArray MainWindow::convertHexStringToAscii(const QString& hexString){
    QByteArray asciiData;
    QStringList hexCodes = hexString.split(' ', Qt::SkipEmptyParts);

    for (const QString &hexCode : hexCodes) {
        bool ok;
        int value = hexCode.toInt(&ok, 16);
        if (ok) {
            asciiData.append(static_cast<char>(value));
        } else {
            return QByteArray();
        }
    }

    return asciiData;
}

void MainWindow::on_pushButtonLCConnect_clicked()
{
    if (!serialPort->isOpen()) {
        QMessageBox::warning(this, "Error", "Serial port not open!");
        return;
    }
    sendCommand("CONN", " 00000");
    currentHeader = "CONN";
}

void MainWindow::sendCommand(const QString& header, const QString& data){
    if (header == "CONN"){}
    else if (header == "READ"){}
    else if (header == "CALB"){}
    else if (header == "OFFS"){}
    else {
        QMessageBox::critical(this, "Error", "Invalid command!");
        return;
    }

    responseBuffer.clear();
    QString command = header + data + "\n";
    serialPort->write(command.toUtf8());
    writeToScreen(command, "red");
    if (header == "CONN") {
        ui->labelLCStatus->setText("Connecting...");
    }
    connect(checkResponseTimer, &QTimer::timeout, this, [this, header]() {
        this->checkResponse(header);
    });
    if (header == "READ"){
        checkResponseTimer->start(lcdUpdateTime);
    }
    else if (header == "CONN" || header == "CALB")
        checkResponseTimer->start(cmdResponseTime);
}

void MainWindow::checkResponse(const QString& header){
    if (header == "CONN"){
        ui->pushButtonLCRead->setEnabled(true);
    }
    if (responseBuffer.left(4) == currentHeader){
        ui->labelLCStatus->setText("Connected");
        connectionTimer->start(lcdUpdateTime);
        ui->pushButtonLCOnOff->setEnabled(true);

        if (responseBuffer.left(4) == "READ") {
            QString subString = responseBuffer.mid(4, 6);
            subString.insert(5, ".");
            bool ok;
            double value = subString.toDouble(&ok);
            updateGraph(value);
            if (ok) {
                ui->lcdNumberWeigth->display(subString);
            } else {
                qDebug() << "Failed to convert substring to float";
            }
        }
        else if (responseBuffer.left(4) == "OFFS") {
            tareFlag = false;
        }
    }
    else {
        ui->labelLCStatus->setText("Disconnected");
        connectionTimer->stop();
        ui->pushButtonLCOnOff->setText("ON");
        ui->pushButtonLCTare->setEnabled(false);
        ui->lcdNumberWeigth->setEnabled(false);
        ui->pushButtonLCRead->setEnabled(false);
        ui->pushButtonLCOnOff->setEnabled(false);
    }
    responseBuffer.clear();
    disconnect(checkResponseTimer, &QTimer::timeout, nullptr, nullptr);
    checkResponseTimer->stop();
}


void MainWindow::on_pushButtonLCOnOff_clicked()
{
    if (ui->pushButtonLCOnOff->text() == "ON"){
        ui->pushButtonLCOnOff->setText("OFF");
        ui->pushButtonLCTare->setEnabled(true);
        ui->lcdNumberWeigth->setEnabled(true);
        ui->pushButtonLCRead->setEnabled(false);
    }
    else if (ui->pushButtonLCOnOff->text() == "OFF"){
        ui->pushButtonLCOnOff->setText("ON");
        ui->pushButtonLCTare->setEnabled(false);
        ui->lcdNumberWeigth->setEnabled(false);
        ui->pushButtonLCRead->setEnabled(true);
    }
}


void MainWindow::on_pushButtonLCRead_clicked()
{
    if (!serialPort->isOpen()) {
        QMessageBox::warning(this, "Error", "Serial port not open!");
        return;
    }
    double value = ui->doubleSpinBoxWeight->value();
    //QString valueString = QString("%0").arg(value, 5, 'f', 0, QChar('0'));
    QString valueString = QString("%1").arg(value, 6, 'f', 1, QChar('0'));
    valueString.remove('.');
    valueString = ' ' + valueString;

    if (value <= 0.0 || value > 5000.0) {
        QMessageBox::warning(this, "Warning", "Invalid value, please re-enter!");
    }
    else {
        sendCommand("CALB", valueString);
        currentHeader = "CALB";
    }
}

void MainWindow::connectionHandler() {
    if (ui->labelLCStatus->text() == "Connected") {
        if (ui->pushButtonLCOnOff->text() == "ON") {
            ui->pushButtonLCRead->setEnabled(true);
        }
        else {
            ui->pushButtonLCRead->setEnabled(false);
        }
        ui->pushButtonLCOnOff->setEnabled(true);
    }
    else if (ui->pushButtonLCOnOff->text() == "ON") {
        ui->pushButtonLCRead->setEnabled(false);
        ui->pushButtonLCOnOff->setEnabled(false);
    }
    if (ui->pushButtonLCOnOff->text() == "OFF" && tareFlag == false) {
        ui->lcdNumberWeigth->setEnabled(true);
        sendCommand("READ", " 00000");
        currentHeader = "READ";
    }
    else
        ui->lcdNumberWeigth->setEnabled(false);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}

void MainWindow::setupGraph(){
    qreal maxValue = std::numeric_limits<qreal>::lowest(); // Initialize with the smallest possible value

    // Iterate through the points in the series
    for (const QPointF &point : series->points()) {
        if (point.y() > maxValue) {
            maxValue = point.y(); // Update maxValue if a larger value is found
        }
    }

    // Access the Graph tab
    QWidget *graphTab = ui->tabWidget->widget(1);

    // Create a layout for the Graph tab
    QVBoxLayout *layout = new QVBoxLayout(graphTab);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Weight");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 10);
    chart->axes(Qt::Horizontal).first()->setRange(0, 10);

    // Create a chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the layout
    layout->addWidget(chartView);

    // Set the layout for the tab
    graphTab->setLayout(layout);
}

void MainWindow::updateGraph(double value)
{
    double max = 0.0;
    double min = 0.0;

    series->clear();                        // Clear the series before appending new data

    for (int i = 0; i < bufferSize; i++) {       // Shift all elements left by 1
        valuetestarray[i] = valuetestarray[i + 1];
    }
    valuetestarray[bufferSize - 1] = value;      // Add the new value at the end

    // Append values from the array to the series
    for (int i = 0; i < bufferSize; i++) {
        series->append(i, valuetestarray[i]);
        if (valuetestarray[i] > max)
            max = valuetestarray[i];
        else if (valuetestarray[i] < min)
            min = valuetestarray[i];
    }

    // Update the chart (ensure series is added only once)
    if (!chart->series().contains(series)) {
        chart->addSeries(series);
        chart->createDefaultAxes(); // This will initialize the axes
    }

    // Set axes range
    chart->axes(Qt::Vertical).first()->setRange(min, max + 10);       // Adjust Y-axis range
    chart->axes(Qt::Horizontal).first()->setRange(0, bufferSize);     // Adjust X-axis range for 10 points
}

void MainWindow::on_pushButton_clicked() {
    //updateGraph(20.0);

    QString subString = responseBuffer.mid(4, 6);
    subString.insert(4, ".");
    bool ok;
    double value = subString.toDouble(&ok);
    updateGraph(value);
    if (ok) {
        ui->lcdNumberWeigth->display(subString);
    } else {
    }
}


void MainWindow::on_pushButtonLCTare_clicked()
{
    tareFlag = true;
    if (!serialPort->isOpen()) {
        QMessageBox::warning(this, "Error", "Serial port not open!");
        return;
    }
    double value = ui->lcdNumberWeigth->value();
    //QString valueString = QString("%0").arg(value, 5, 'f', 0, QChar('0'));
    QString valueString = QString("%1").arg(value, (value >= 0) ? 6: 7, 'f', 1, QChar('0'));
    valueString.remove('.');
    if (value >= 0.0)
        valueString = ' ' + valueString;

    sendCommand("OFFS", valueString);
    currentHeader = "OFFS";
}

