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
  void ending();
  void finished();
  void error(QString err);

 public slots:
  void doWork();
  void getMSG();
  void setEnding(bool status);
  void setEnding();
  void setSending();

 private:
  quint16 _port = 0;
  Socket *mySocketGet = NULL;
  bool statusRead = false;
};

#endif  // SERVER_H
