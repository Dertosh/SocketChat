#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "socket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int id = 555;
    QString nickname = "Batman";
    QAbstractSocket mySocket = new Socket(UnknownSocketType, 0);
    int _port = 61000;
    mySocket.connectToHost("127.0.0.1", _port);
    ui->mesgOut->append("Hellow world!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
