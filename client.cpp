#include "client.h"
#include <QEventLoop>
#include <QTextStream>
#include <QThread>
#include <QtDebug>
QTextStream cout(stdout);

Client::Client(int port) { _port = port; }
Client::~Client() {
  mySocketSend->disconnectFromHost();
  mySocketSend->close();
  qDebug() << "Disconnect " << mySocketSend->waitForDisconnected(1000);
  delete mySocketSend;
  qDebug("Client: Exit");
}

void Client::doWork() {
  // NativeSocket* sok = new NativeSocket();
  // sok->connectToHost(SO_REUSEADDR | SO_REUSEPORT, 1, uint16_t(8080));
  if (mySocketSend != NULL) return;
  mySocketSend = new Socket(10);
  // mySocketSend->connectToHost("127.0.0.1", _port);
  QThread::sleep(1);
  mySocketSend->connectToHost(QHostAddress::LocalHost, _port,
                              QIODevice::WriteOnly);
  qDebug() << "client" << mySocketSend->peerAddress();
  // qDebug() << "client open =" <<
  // mySocketSend->open(QAbstractSocket::WriteOnly);
  mySocketSend->setSocketDescriptor(Socket::MySocket, Socket::ConnectedState,
                                    Socket::WriteOnly);
  qDebug() << "client: connected " << mySocketSend->waitForConnected(10000);
  // mySocketSend->setSocketOption(Socket::KeepAliveOption);
  // qDebug() << "connected client " <<
  mySocketSend->waitForConnected(1000);
  qDebug() << "client: state = " << mySocketSend->state();
  qDebug() << "client: state = " << mySocketSend->state();
  QString text =
      "Hellow world! Почему не работает "
      "передача?";
  qDebug() << text;
  QByteArray temp(text.toLocal8Bit());
  const char* charmass = text.toLocal8Bit();
  // qDebug() << text.toLocal8Bit();
  size_t i = 0;
  QEventLoop loop;
  this->sending();
  connect(this, SIGNAL(isSending()), this, SLOT(sending()));
  connect(this, SIGNAL(isSending()), &loop, SLOT(quit()));
  loop.exec();
  qDebug() << "client: exit";
}

void Client::setStatusSending(bool status) {
  qDebug() << "status -" << status;
  statusSend = status;
  if (status == true) isSending();
}

void Client::sending() {
  //  qDebug() << "client: state = " << mySocketSend->state();
  //  QString text =
  //      "Hellow world! Почему не работает "
  //      "передача?";
  //    qDebug() << text;
  //  QByteArray temp(text.toLocal8Bit());
  //  const char* charmass = text.toLocal8Bit();
  //  // qDebug() << text.toLocal8Bit();
  //  size_t i = 0;
  // while (statusSend) {
  // temp = text.toLocal8Bit();
  // qDebug() << temp;
  // mySocketSend->write(qint32(10));
  // qDebug() << "client: connected " <<
  // mySocketSend->waitForConnected(1000); qDebug() << "waitread = " <<
  // mySocketSend->waitForReadyRead(1000);
  qDebug() << "client: isopen " << mySocketSend->isOpen();
  qDebug() << "client: isW " << mySocketSend->isWritable();
  qDebug() << "client: "
           << "test"
           << "bit = " << mySocketSend->write("hello world");
  qDebug() << "client: " << mySocketSend->error();
  // qDebug() << i
  //         << "bit = " <<
  //         mySocketSend->write(text.toLocal8Bit(),
  //         qint64(16));
  qDebug() << "client: waitBytesWritten "
           << mySocketSend->waitForBytesWritten(1000);
  qDebug() << "client: Error: " << mySocketSend->errorString() << "n "
           << mySocketSend->error();
}
