#include "socket.h"

Socket::Socket(int socketNumber, SocketType socketType, QObject *parent)
    : QAbstractSocket(QAbstractSocket::UnknownSocketType, NULL) {
  // this->setSocketDescriptor(3);
  // https://doc.qt.io/archives/3.3/clientserver-example.html
}

qint64 Socket::sendData(const char *data, qint64 size) {
  return writeData(data, size);
}
