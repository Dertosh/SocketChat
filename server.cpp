#include "server.h"
#include "socket.h"

Server::Server(QObject *parent, size_t port) : QObject(parent) { _port = port; }

Server::~Server() { qDebug("Exit"); }

void Server::doWork() {
  Socket *mySocketGet = new Socket(2);
  mySocketGet->connectToHost(QHostAddress::Any, _port, QIODevice::ReadOnly);
  mySocketGet->setSocketDescriptor(Socket::MySocket, Socket::ConnectedState,
                                   Socket::ReadOnly);
  qDebug() << "window " << mySocketGet->waitForConnected(1000);
  qDebug() << "window " << mySocketGet->open(QIODevice::ReadOnly);
  qDebug() << "window " << mySocketGet->state();
  qDebug() << "server Hellow world!";
  QString buff = "bindStatus = ";
  // mesgWindow->append(answer);
  // while (mySocketGet->isReadable()) {
  // mySocketGet->open(QIODevice::ReadOnly);
  // mySocketGet->readyRead();
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
  for (int i = 1; i <= 50; i++) {
    qDebug() << mySocketGet->waitForReadyRead(10000);
    QByteArray arr = mySocketGet->read(10);
    mySocketGet->waitForBytesWritten(10000);
    // qDebug() << arr;
    qDebug() << "new " << QString::number(i);
    qDebug() << QString::fromLocal8Bit(arr);
  }
  mySocketGet->disconnectFromHost();
  mySocketGet->close();
  delete mySocketGet;
}
