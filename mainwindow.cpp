#include "mainwindow.h"
#include "socket.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  int id = 555;
  QString nickname = "Batman";
  Socket *mySocketSend = new Socket(1);
  Socket *mySocketGet = new Socket(2);
  int _port = 6200;

  mySocketSend->connectToHost(QHostAddress::LocalHost, _port);
  mySocketGet->connectToHost(QHostAddress::LocalHost, _port);

  mySocketSend->write("test data");

  // bool bindStatus = mySocket1->bind(QHostAddress::LocalHost, _port);
  // qDebug() << "bindStatus = " << bindStatus << endl;
  QTextBrowser *mesgWindow = ui->mesgOut;
  mesgWindow->append("Hellow world!");
  QString buff = "bindStatus = ";
  // buff.append((bindStatus + 1) * 10);
  mesgWindow->append(buff);

  // while (mySocketGet->isReadable()) {
  QByteArray arr = mySocketGet->readAll();
  mesgWindow->append(arr);
  //}
}

MainWindow::~MainWindow() { delete ui; }
