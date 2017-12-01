#include "SerialConsole.h"
#include "ui_SerialConsole.h"
#include "console.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

//! [0]
SerialConsole::SerialConsole(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialConsole)
{
    firstData = true;
//! [0]
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
    setCentralWidget(console);
//! [1]
    serial = new QSerialPort(this);
//! [1]
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

//! [2]
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
//! [2]
   // connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
//! [3]
}
//! [3]

SerialConsole::~SerialConsole()
{
    delete settings;
    delete ui;
}

//! [4]
void SerialConsole::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            console->setEnabled(true);
            //serial->setReadBufferSize(52);
            console->setLocalEchoEnabled(false);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
            emit serialConnected();
            //readTimer.start();
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void SerialConsole::closeSerialPort()
{
    serial->close();
    //console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
    data.clear();
    firstData = true;
   // readTimer.stop();
    emit serialDisconnected();
}
//! [5]

void SerialConsole::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void SerialConsole::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
void SerialConsole::readData()
{
    data.append(serial->readAll());
    if (firstData) {
        if (data.length()>=52) {
            if (data[0] != (char)1){
                console->putData("First data received was out of line. Correcting...: ");
                console->putData(data);
                data=data.remove(0, data.indexOf((char)1));
                firstData = false;
            } else {
                firstData = false;
            }
        }
    } else {
        if (data.length()==52) {
            emit dataReceived(data);
            data.clear();
        } else if (data.length() > 52) {
            // Signal processing fell behind and read more characters
            // than it should have. We need to handle this or else
            // we will effective stop reading data.
            /*
         * A couple options:
         *  1) Pass along each full transmission we have in succession.
         *  2) Consider past transmissions a lost cause and drop the data.
         *
         * I think for now we will go with option 1, unless that proves
         * to be not good. I think the system ought to catch up
         * if it gets in this scenario.
         */

            emit dataReceived(data.left(52));
            data = data.remove(0, 52);

        }
    }
}
//! [7]

//! [8]
void SerialConsole::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void SerialConsole::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

Console *SerialConsole::getConsole() const
{
    return console;
}
