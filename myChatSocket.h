#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QDataStream>
#include <QEventLoop>
#include <QLoggingCategory>
#include <QObject>
#include <QUdpSocket>
#include "hamming.h"
Q_DECLARE_LOGGING_CATEGORY(logMyChat)

class myChat : public QObject {
  Q_OBJECT

 public:
  myChat(QString nickname, quint16 port);
  ~myChat();

 signals:
  void ready();
  void showMSG(QString);
  void showMSG(qint8, QString, QString);
  void showPersonalMSG(QString);

 public slots:
  void send(QString str, qint8 typeMSG);
  void read();
  void process();
  void stop();
  void run();

 private:
  QUdpSocket *chatSocket = nullptr;  //Сокет для приема и передачи сообщений
  quint16 _port;      //порт сокета
  QString _nickname;  //Имя пользователя
  bool m_running;

  QString decodeMSG(QString);
  QString encodeMSG(QString);
};

#endif  // AUTHSOCKET_H
