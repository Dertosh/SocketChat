#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QDataStream>
#include <QEventLoop>
#include <QLoggingCategory>
#include <QObject>
#include <QUdpSocket>
Q_DECLARE_LOGGING_CATEGORY(logAuthSocket)

class myChat : public QObject {
  Q_OBJECT

 public:
  myChat(quint16 port);
  ~myChat();

 signals:
  void ready();
  void showMSG(QString);

 public slots:
  void send(QString str, qint8 typeMSG);
  void read();
  void process();
  void stop();
  void run();

 private:
  QUdpSocket *chatSocket = nullptr;
  quint16 _port;
  bool m_running;
};

#endif  // AUTHSOCKET_H
