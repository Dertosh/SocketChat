#include "myChatSocket.h"
Q_LOGGING_CATEGORY(logMyChat, "myChat")

myChat::myChat(QString nickname, quint16 port, QNetworkInterface interface)
    : _port(port),
      _nickname(nickname),
      brd(interface.addressEntries().first().broadcast()) {
  test(21);
}

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
  out << encodeMSG(str);
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
  QVector<uint32_t> str;
  in >> str;

  qDebug(logMyChat()) << "Hcheck: " << checkMSG(str);

  // qDebug(logMyChat()) << "sender:_" << sender << ", nick:_" << _nickname <<
  // ".";
  emit showMSG(sender, decodeMSG(str));
  qDebug(logMyChat()) << "type:" << type << "read :" << str;
}

void myChat::process() {
  chatSocket = new QUdpSocket(this);
  chatSocket->bind(QHostAddress::Any, _port);
  // chatSocket->setMulticastInterface(_interface);
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
    msg_out.append(int(hammingEncode(encode(c.unicode(), 21), 21)));
  return msg_out;
}

size_t myChat::checkMSG(QVector<uint32_t> msg) {
  size_t check = 0;
  foreach (QChar c, msg) { check += hammingCheck(c.unicode(), 21); }
  return check;
}

void myChat::run() { m_running = true; }
void myChat::stop() { m_running = false; }
