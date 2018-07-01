#include "myChatSocket.h"
Q_LOGGING_CATEGORY(logMyChat, "myChat")

myChat::myChat(QString nickname, quint16 port)
    : _port(port), _nickname(nickname) {}

myChat::~myChat() {
  chatSocket->close();
  qDebug(logMyChat()) << "close";
};

void myChat::send(QString str, qint8 typeMSG) {
  qDebug(logMyChat()) << "port" << QString::number(chatSocket->localPort());
  qDebug(logMyChat()) << "Sending...";
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << qint64(0);
  out << qint8(typeMSG);
  out << _nickname;
  out << str;
  out.device()->seek(qint64(0));
  out << qint64(data.size() - sizeof(qint64));
  chatSocket->writeDatagram(data, QHostAddress::Broadcast, _port);
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
  // QHostAddress *address = new QHostAddress();
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
  QString str;
  in >> str;
  QString msg;
  if (sender == _nickname)
    msg = "<div style=\"text-align: left\"><font color=\"DarkBlue\">";
  else
    msg = "<div style=\"text-align: right\"><font color=\"DarkBlue\">";
  msg += sender + ": </font>" + str + "</div>";
  emit showMSG(msg);
  qDebug(logMyChat()) << "type:" << type << "read :" << str;
}

void myChat::process() {
  chatSocket = new QUdpSocket();
  chatSocket->bind(QHostAddress::Any, _port);
  connect(chatSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

void myChat::run() { m_running = true; }
void myChat::stop() { m_running = false; }
