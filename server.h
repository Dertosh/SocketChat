#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "nativesocket.h"
#include "socket.h"

class Server : public QObject {
  Q_OBJECT
 public:
  explicit Server(QObject *parent = nullptr, size_t = 0);
  ~Server();

 signals:
  void finished();
  void error(QString err);

 public slots:
  void doWork();

 private:
  quint16 _port = 0;
};

#endif  // SERVER_H
