#include "client.h"
#include <QTextStream>
#include <QtDebug>
QTextStream cout(stdout);

Client::Client(int port) { _port = port; }
Client::~Client() { qDebug("Exit"); }

void Client::doWork() {
  Socket *mySocketSend = new Socket(10);
  // mySocketSend->connectToHost("127.0.0.1", _port);
  qDebug() << "bind " << mySocketSend->bind(QHostAddress("127.0.0.1"), _port);
  mySocketSend->setSocketDescriptor(Socket::MySocket, Socket::ConnectedState,
                                    Socket::WriteOnly);
  qDebug() << "connected " << mySocketSend->waitForConnected(1000);
  qDebug() << "state = " << mySocketSend->state();
  QString text = "Hellow world! Почему не работает передача?\r\n";
  qDebug() << text;
  QByteArray temp(text.toLocal8Bit());
  // qDebug() << text.toLocal8Bit();
  for (int i = 1; i > 0; --i) {
    // temp = text.toLocal8Bit();
    // qDebug() << temp;
    // mySocketSend->write(qint32(10));
    qDebug() << "connected " << mySocketSend->waitForConnected(1000);
    qDebug() << "bit = " << mySocketSend->write(temp);
    qDebug() << "Error " << mySocketSend->errorString() << "n "
             << mySocketSend->error();
    qDebug() << "wait " << mySocketSend->waitForBytesWritten(1000);
  }
  delete mySocketSend;
}
