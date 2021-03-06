﻿#include "myChatSocket.h"
Q_LOGGING_CATEGORY(logMyChat, "myChat")

myChat::myChat(QString nickname, quint16 port, QNetworkInterface &interface)
    : _port(port), _nickname(nickname) {
  foreach (QNetworkAddressEntry address, interface.addressEntries()) {
    if (address.broadcast().toString().contains(".255")) {
      brd = address.broadcast();
      break;
    }
  }
}  //сохраняем бродкаст адресс

myChat::~myChat() {
  chatSocket->disconnectFromHost();
  chatSocket->close();
  qDebug(logMyChat()) << "close";
};

void myChat::send(qint8 typeMSG) { emit send("", typeMSG); }

void myChat::send(QString str, qint8 typeMSG) {
  qDebug(logMyChat()) << "Sending...";
  qDebug(logMyChat()) << "broadcast: " << brd.toString();
  qDebug(logMyChat()) << "port" << QString::number(chatSocket->localPort())
                      << "type " << typeMSG;
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << qint64(0);
  out << qint8(typeMSG);
  out << _nickname;
  if (typeMSG == 1) out << encodeMSG(str);
  out.device()->seek(qint64(0));
  out << qint64(data.size() - sizeof(qint64));
  chatSocket->writeDatagram(data, brd, _port);
  qDebug(logMyChat()) << "Sended";
}

void myChat::read() {
  qDebug(logMyChat()) << "reading...";
  QByteArray datagram;
  if (!chatSocket->hasPendingDatagrams()) {
    qDebug(logMyChat()) << "no datagrams";
    qDebug(logMyChat()) << "Staus - " << chatSocket->error();
    return;
  }
  datagram.resize(chatSocket->pendingDatagramSize());
  chatSocket->readDatagram(datagram.data(), datagram.size());
  QDataStream in(&datagram, QIODevice::ReadOnly);

  qint64 size = -1;
  if (in.device()->size() > sizeof(qint64)) {
    in >> size;
  } else
    return;
  if (in.device()->size() - sizeof(qint64) < size) return;
  qint8 type = 0;
  in >> type;
  QString sender;
  in >> sender;
  QVector<uint32_t> str;
  switch (type) {
    case 1:
      in >> str;
      qDebug(logMyChat()) << "Hcheck: " << checkMSG(str);
      emit showMSG(sender, decodeMSG(str));
      qDebug(logMyChat()) << "type:" << type << "read :" << str;
      break;
    case 2:
      qDebug(logMyChat()) << "type:" << type << "TEST";
      break;
    default:
      qDebug(logMyChat()) << "type:" << type << "ERROR";
      break;
  }
}

void myChat::process() {
  chatSocket = new QUdpSocket(this);
  chatSocket->bind(
      QHostAddress::Any,
      _port);  //закрепляем за сокетом адресс и порт для прослушивания
  connect(chatSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

QString myChat::decodeMSG(QVector<uint32_t> msg) {
  QString msg_out;
  foreach (QChar c, msg) {
    msg_out.append(decode(hammingCorrection(c.unicode(), 21), 21));
  }
  return msg_out;
}

QVector<uint32_t> myChat::encodeMSG(QString msg) {
  QVector<uint32_t> msg_out;
  foreach (QChar c, msg)
    msg_out.append(hammingEncode(encode(c.unicode(), 21), 21));
  return msg_out;
}

size_t myChat::checkMSG(QVector<uint32_t> msg) {
  size_t check = 0;
  foreach (QChar c, msg) { check += hammingCheck(c.unicode(), 21); }
  return check;
}

QString myChat::getNickname() { return _nickname; }

quint16 myChat::getPort() { return _port; }

void myChat::run() { m_running = true; }
void myChat::stop() { m_running = false; }
