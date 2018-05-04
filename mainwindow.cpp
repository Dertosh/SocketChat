#include "mainwindow.h"
#include <QtDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  int id = 555;
  QString nickname = "Batman";
  Socket *mySocketSend = new Socket(1);
  Socket *mySocketGet = new Socket(2);
  int _port = 61111;
  qDebug("nickname");
  Client *client = new Client(61111);
  client->moveToThread(&sendThread);
  connect(&sendThread, &QThread::finished, client, &QObject::deleteLater);
  connect(&sendThread, SIGNAL(started()), client, SLOT(doWork()));
  sendThread.start();

  // mySocketSend->connectToHost(QHostAddress::LocalHost, _port);
  mySocketGet->connectToHost(QHostAddress::LocalHost, _port,
                             QIODevice::ReadOnly);

  // mySocketSend->write("test data");

  // bool bindStatus = mySocket1->bind(QHostAddress::LocalHost, _port);
  // qDebug() << "bindStatus = " << bindStatus << endl;
  QTextBrowser *mesgWindow = ui->mesgOut;
  mesgWindow->append("Hellow world!");
  QString buff = "bindStatus = ";
  // buff.append((bindStatus + 1) * 10);
  QString answer = "No";
  if (sendThread.isRunning()) answer = "Yes";
  mesgWindow->append(answer);
  // while (mySocketGet->isReadable()) {
  mySocketGet->readyRead();
  int t = 'А';
  mesgWindow->append(QString::number(t));
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
  mesgWindow->append(test);
  for (int i = 100; i > 0; i--) {
    char arr[10];
    for (int var = 0; var < 10; ++var) {
      arr[var] = 'C';
    }
    mySocketGet->readLine(arr, 10);

    // if (*arr == 'П' and *(arr + 1) == 'П') {
    mesgWindow->append(QString::fromLocal8Bit(arr));
    //}
  }
  //}
}

MainWindow::~MainWindow() {
  delete ui;
  sendThread.quit();
  sendThread.wait();
}
