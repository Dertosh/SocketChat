#include "socket.h"

Socket::Socket(int socketNumber, SocketType socketType, QObject *parent)
    : QAbstractSocket(QAbstractSocket::UnknownSocketType, NULL) {
  this->setSocketDescriptor(3);
  // https://doc.qt.io/archives/3.3/clientserver-example.html
}
