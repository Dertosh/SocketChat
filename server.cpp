#include "server.h"
#include <QEventLoop>
#include <QThread>
#include "socket.h"

Server::Server(QObject* parent, size_t port) : QObject(parent) { _port = port; }

Server::~Server() {
  mySocketGet->disconnectFromHost();
  mySocketGet->close();
  delete mySocketGet;
  qDebug("Server: Exit");
}

void Server::doWork() {
  // NativeSocket* sok = new NativeSocket();
  // sok->sendMSG();
  mySocketGet = new Socket(2);
  qDebug() << "server: bind "
           << mySocketGet->bind(QHostAddress::Any, _port,
                                QAbstractSocket::ShareAddress);
  mySocketGet->setSocketDescriptor(Socket::MySocket, Socket::ConnectedState,
                                   Socket::ReadOnly);
  qDebug() << "server: connect status" << mySocketGet->waitForConnected(20000);
  // qDebug() << "server: " <<
  // mySocketGet->waitForConnected(10000);
  // qDebug() << "window " <<
  // mySocketGet->open(QIODevice::ReadOnly);
  qDebug() << "server: " << mySocketGet->state();
  qDebug() << "server Hellow world!";
  QString buff = "bindStatus = ";
  // mesgWindow->append(answer);
  // while (mySocketGet->isReadable()) {
  // mySocketGet->open(QIODevice::ReadOnly);
  // mySocketGet->readyRead();
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
  // for (int i = 1; i <= 50; i++) {
  QEventLoop loop;
  loop.connect(this, SIGNAL(finished()), SLOT(quit()));
  loop.exec();
}

void Server::getMSG() {
  qDebug() << "server: " << mySocketGet->state();
  this->statusRead = true;
  // qDebug() << "server: " << mySocketGet->peerAddress();
  while (this->statusRead) {
    QThread::sleep(1);
    qDebug() << "Client: test msg" << this->statusRead;
    if (!mySocketGet->waitForReadyRead(100000)) continue;
    QByteArray arr = mySocketGet->readLine();
    mySocketGet->waitForBytesWritten(100000);
    // qDebug() << arr;
    qDebug() << "Server: new ";  //<< QString::number(i);
    qDebug() << "Server: text: " << QString::fromLocal8Bit(arr);
  };
}

void Server::setEnding(bool status) {
  qDebug() << "statusRead" << status;
  statusRead = status;
}

void Server::setEnding() {
  this->statusRead = false;
  qDebug() << "statusRead" << statusRead;
}

void Server::setSending() {
  this->statusRead = true;
  qDebug() << "statusRead" << statusRead;
}
