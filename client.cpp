#include "client.h"
#include <QTextStream>
#include <QtDebug>
QTextStream cout(stdout);

Client::Client(int port) { _port = port; }
Client::~Client() { qDebug("Exit"); }

void Client::doWork() {
  // NativeSocket* sok = new NativeSocket();
  // sok->connectToHost(SO_REUSEADDR | SO_REUSEPORT, 1, uint16_t(8080));
  Socket* mySocketSend = new Socket(10);
  // mySocketSend->connectToHost("127.0.0.1", _port);
  qDebug() << "bind "
           << mySocketSend->bind(QHostAddress::Broadcast, _port,
                                 QAbstractSocket::ShareAddress |
                                     QAbstractSocket::ReuseAddressHint);
  // qDebug() << "client open =" <<
  mySocketSend->open(QAbstractSocket::WriteOnly);
  mySocketSend->setSocketDescriptor(Socket::MySocket, Socket::ConnectedState,
                                    Socket::WriteOnly);
  qDebug() << "connected client " << mySocketSend->waitForConnected(1000);
  qDebug() << "client state = " << mySocketSend->state();
  QString text =
      "Hellow world! Почему не работает "
      "передача?";
  qDebug() << text;
  QByteArray temp(text.toLocal8Bit());
  const char* charmass = text.toLocal8Bit();
  // qDebug() << text.toLocal8Bit();
  for (int i = 1; i < 10; ++i) {
    // temp = text.toLocal8Bit();
    qDebug() << temp;
    // mySocketSend->write(qint32(10));
    qDebug() << "client connected " << mySocketSend->waitForConnected(1000);
    // qDebug() << "waitread = " <<
    // mySocketSend->waitForReadyRead(1000);
    qDebug() << "isopen " << mySocketSend->isOpen();
    qDebug() << "isW " << mySocketSend->isWritable();
    qDebug() << i << "bit = " << mySocketSend->write("hello world");
    // qDebug() << i
    //         << "bit = " <<
    //         mySocketSend->write(text.toLocal8Bit(),
    //         qint64(16));
    qDebug() << "wait client" << mySocketSend->waitForBytesWritten(1000);
    qDebug() << "client Error " << mySocketSend->errorString() << "n "
             << mySocketSend->error();
  }
  mySocketSend->disconnectFromHost();
  mySocketSend->close();
  qDebug() << "Disconnect " << mySocketSend->waitForDisconnected(1000);
  delete mySocketSend;
}
