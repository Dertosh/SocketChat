#include "mainwindow.h"
#include <QtDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  int id = 555;
  QString nickname = "Batman";
  Socket *mySocketGet = new Socket(2);
  quint16 _port = 64101;
  qDebug("nickname");
  Client *client = new Client(_port);
  client->moveToThread(&sendThread);
  connect(&sendThread, &QThread::finished, client, &QObject::deleteLater);
  connect(&sendThread, SIGNAL(started()), client, SLOT(doWork()));
  sendThread.start();

  // mySocketSend->connectToHost(QHostAddress::LocalHost, _port);
  mySocketGet->connectToHost(QHostAddress::AnyIPv4, _port, QIODevice::ReadOnly);
  mySocketGet->setSocketDescriptor(Socket::MySocket);

  // mySocketSend->write("test data");

  // bool bindStatus = mySocket1->bind(QHostAddress::LocalHost, _port);
  // qDebug() << "bindStatus = " << bindStatus << endl;
  QTextBrowser *mesgWindow = ui->mesgOut;
  qDebug() << "window " << mySocketGet->waitForConnected(1000);
  qDebug() << "window " << mySocketGet->state();
  mesgWindow->append("Hellow world!");
  QString buff = "bindStatus = ";
  // buff.append((bindStatus + 1) * 10);
  QString answer = "No";
  if (sendThread.isRunning()) answer = "Yes";
  mesgWindow->append(answer);
  // while (mySocketGet->isReadable()) {
  // mySocketGet->open(QIODevice::ReadOnly);
  // mySocketGet->readyRead();
  int t = 'А';
  mesgWindow->append(QString::number(t));
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
  mesgWindow->append(test);
  for (int i = 50; i > 0; i--) {
    mySocketGet->waitForReadyRead(10000);
    QByteArray arr = mySocketGet->readLine();
    // qDebug() << arr;
    mesgWindow->append("new");
    mesgWindow->append(QString::fromLocal8Bit(arr));
  }
  delete mySocketGet;
}

MainWindow::~MainWindow() {
  delete ui;
  sendThread.quit();
  sendThread.wait();
}
