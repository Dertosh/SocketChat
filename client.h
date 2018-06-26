#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include "nativesocket.h"
#include "socket.h"

class Client : public QObject {
  Q_OBJECT
 public:
  Client(int = 0);
  ~Client();
 public slots:
  void doWork();
  void setStatusSending(bool status);
  void sending();
 signals:
  void finished();
  void error(QString err);
  void isSending();

 private:
  quint16 _port = 0;
  Socket* mySocketSend = NULL;
  bool statusSend = false;
};

#endif  // CLIENT_H
