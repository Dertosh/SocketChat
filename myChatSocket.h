#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QDataStream>
#include <QEventLoop>
#include <QLoggingCategory>
#include <QNetworkInterface>
#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include "hamming.h"
Q_DECLARE_LOGGING_CATEGORY(logMyChat)

class myChat : public QObject {
  Q_OBJECT

 public:
  myChat(QString nickname, quint16 port, QNetworkInterface &interface);
  ~myChat();

 signals:
  void ready();
  void showMSG(QString);
  void showMSG(QString, QString);
  void showPersonalMSG(QString);

 public slots:
  void send(QString str, qint8 typeMSG);
  void send(qint8 typeMSG);
  void read();
  void process();
  void stop();
  void run();

  QString getNickname();
  quint16 getPort();

 private:
  QUdpSocket *chatSocket = nullptr;  //Сокет для приема и передачи сообщений
  quint16 _port;      //порт сокета
  QString _nickname;  //Имя пользователя
  QHostAddress brd;
  bool m_running;

  QString decodeMSG(QVector<uint32_t>);
  QVector<uint32_t> encodeMSG(QString);
  size_t checkMSG(QVector<uint32_t>);
};

#endif  // AUTHSOCKET_H
