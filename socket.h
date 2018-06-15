#ifndef SOCKET_H
#define SOCKET_H

#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QIODevice>
#include <QObject>

class Q_NETWORK_EXPORT Socket : public QAbstractSocket {
  Q_OBJECT

 public:
  enum SocketType {
    TcpSocket,
    UdpSocket,
    SctpSocket,
    MySocket,
    UnknownSocketType = -1
  };
  Q_ENUM(SocketType)

  explicit Socket(int, SocketType = MySocket, QObject* = Q_NULLPTR);

  qint64 sendData(const char*, qint64);

  ~Socket() {}
};

#endif  // SOCKET_H
