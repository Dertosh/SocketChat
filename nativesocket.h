#ifndef NATIVESOCKET_H
#define NATIVESOCKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <QObject>
#include <QtDebug>

class NativeSocket : public QObject {
  Q_OBJECT

  int _socket_fd;
  int _new_socket;
  struct sockaddr_in _address;

 public:
  explicit NativeSocket(QObject *parent = nullptr);

  bool connectToHost(int type, int openMode, uint16_t port);
  int sendMSG();

 signals:

 public slots:
};

#endif  // NATIVESOCKET_H
