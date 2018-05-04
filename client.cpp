#include "client.h"
#include <QTextStream>
#include <QtDebug>
QTextStream cout(stdout);

Client::Client(int port) { _port = port; }
Client::~Client() { qDebug("Exit"); }

void Client::doWork() {
  Socket *mySocketSend = new Socket(10);
  mySocketSend->connectToHost("127.0.0.1", _port, QIODevice::WriteOnly);
  qDebug() << "connected " << mySocketSend->isWritable();
  char *text = "Почему не работает передача?";
  qDebug() << text;
  for (int i = 10; i > 0; --i) {
    int bit = mySocketSend->write(text);
    qDebug() << "bit = " << bit;
    qDebug() << "wait " << mySocketSend->waitForBytesWritten(1000);
  }
}
