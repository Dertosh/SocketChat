#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QDataStream>
#include <QEventLoop>
#include <QLoggingCategory>
#include <QObject>
#include <QUdpSocket>
Q_DECLARE_LOGGING_CATEGORY(logAuthSocket)

class AuthSocket : public QObject {
  Q_OBJECT

 public:
  AuthSocket(quint16 port);
  ~AuthSocket();

 signals:
  void ready();

 public slots:
  void send(QString str, qint8 typeMSG);
  void read();
  void process();
  void stop();
  void run();

 private:
  QUdpSocket *authSocket = nullptr;
  quint16 _port;
  bool m_running;
};

#endif  // AUTHSOCKET_H
