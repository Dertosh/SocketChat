#include "socket.h"

Socket::Socket(int socketNumber, SocketType socketType, QObject *parent)
    : QAbstractSocket(QAbstractSocket::UnknownSocketType, NULL) {}

qint64 Socket::sendData(const char *data, qint64 size) {
  return writeData(data, size);
}
