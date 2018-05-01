#ifndef SOCKET_H
#define SOCKET_H

#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QObject>

class Socket : public QAbstractSocket {
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

  Socket(int socketNumber, SocketType = MySocket, QObject* = 0);

  ~Socket() {}
};

#endif  // SOCKET_H
