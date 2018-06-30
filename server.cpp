#include "server.h"
#include <QEventLoop>
#include <QThread>
#include "socket.h"
Q_LOGGING_CATEGORY(logCategoryServer, "Server")

Server::Server(size_t port) {
  _port = port;
  serverSocket = new QTcpServer();
  QUdpSocket *authSocket = new QUdpSocket();
  // authSocket->bind(QHostAddress::Any, _port);
  connect(authSocket, SIGNAL(readyRead()), SLOT(read()));
}

Server::~Server() {
  serverSocket->disconnect();
  serverSocket->close();
  delete serverSocket;
  qDebug("Server: Exit");
}

void Server::doWork() {
  // qDebug() << "Server: connect status" << authSocket->waitForConnected();

  // qDebug() << "Server: Listening:"
  //         << serverSocket->listen(QHostAddress::Any, _port);
  // qDebug() << "server: connect status" <<
  // serverSocket->waitForConnected(20000);
  // qDebug() << "server: " <<
  // mySocketGet->waitForConnected(10000);
  // qDebug() << "window " <<
  // mySocketGet->open(QIODevice::ReadOnly);
  qDebug() << "server Hellow world!";
  QString buff = "bindStatus = ";
  // mesgWindow->append(answer);
  // while (mySocketGet->isReadable()) {
  // mySocketGet->open(QIODevice::ReadOnly);
  // mySocketGet->readyRead();
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
  // emit finished();
  QEventLoop loop;
  connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();
  qDebug(logCategoryServer()) << "end loop";
}

void Server::read() {
  qDebug(logCategoryServer()) << "reading...";
  qDebug(logCategoryServer()) << "Staus - " << authSocket->errorString();
  QByteArray datagram;
  if (authSocket->hasPendingDatagrams()) return;
  datagram.resize(authSocket->pendingDatagramSize());
  QHostAddress *address = new QHostAddress();
  authSocket->readDatagram(datagram.data(), datagram.size());
  qDebug(logCategoryServer()) << "read -" << datagram.data();
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
