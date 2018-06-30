#ifndef CLIENT_H
#define CLIENT_H
#include <QDataStream>
#include <QEventLoop>
#include <QLoggingCategory>
#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QUdpSocket>
#include <QtDebug>
#include "nativesocket.h"
#include "socket.h"
Q_DECLARE_LOGGING_CATEGORY(logCategoryClient)

class Client : public QObject {
  Q_OBJECT
 public:
  Client(int = 0);
  ~Client();
 public slots:
  void doWork();
  void setStatusSending(bool status);
  void sending(QString str, qint8 typeMSG);
 signals:
  void finished();
  void error(QString err);
  void isSending();

 private:
  quint16 _port = 0;
  QTcpSocket* clientSocket = nullptr;
  bool statusSend = false;
  QUdpSocket* authSocket = nullptr;
};

#endif  // CLIENT_H
