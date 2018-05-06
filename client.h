#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include "socket.h"

class Client : public QObject {
  Q_OBJECT
 public:
  Client(int = 61111);
  ~Client();
 public slots:
  void doWork();
 signals:
  void finished();
  void error(QString err);

 private:
  quint16 _port = 0;
};

#endif  // CLIENT_H
