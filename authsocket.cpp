#include "authsocket.h"
Q_LOGGING_CATEGORY(logAuthSocket, "AuthSocket")

AuthSocket::~AuthSocket() {
  authSocket->close();
  qDebug(logAuthSocket()) << "authSocket close";
}

AuthSocket::AuthSocket(quint16 port) { _port = port; }

void AuthSocket::send(QString str, qint8 typeMSG) {
  // QEventLoop loop;
  // connect(this, SIGNAL(ready()), &loop, SLOT(quit()));
  // loop.exec();
  qDebug(logAuthSocket()) << "port" << QString::number(authSocket->localPort());
  qDebug(logAuthSocket()) << "Sending...";
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << qint64(0);
  out << qint8(typeMSG);
  out << str;
  out.device()->seek(qint64(0));
  out << qint64(data.size() - sizeof(qint64));
  authSocket->writeDatagram(data, QHostAddress::Broadcast, _port);
  qDebug(logAuthSocket()) << "Sended";
}

void AuthSocket::read() {
  qDebug(logAuthSocket()) << "reading...";
  qDebug(logAuthSocket()) << "read status" << authSocket->waitForReadyRead();
  QByteArray datagram;
  if (!authSocket->hasPendingDatagrams()) {
    qDebug(logAuthSocket()) << "no datagrams";
    qDebug(logAuthSocket()) << "Staus - " << authSocket->error();
    return;
  }
  datagram.resize(authSocket->pendingDatagramSize());
  QHostAddress *address = new QHostAddress();
  authSocket->readDatagram(datagram.data(), datagram.size());
  QDataStream in(&datagram, QIODevice::ReadOnly);

  qint64 size = -1;
  if (in.device()->size() > sizeof(qint64)) {
    in >> size;
  } else
    return;
  if (in.device()->size() - sizeof(qint64) < size) return;
  qint8 type = 0;
  in >> type;
  QString str;
  in >> str;
  qDebug(logAuthSocket()) << "type:" << type << "read :" << str;
}

void AuthSocket::process() {
  // QEventLoop loop;
  // QObject::connect(this, SIGNAL(stop()), &loop, SLOT(quit()),
  //                 Qt::QueuedConnection);

  // loop.exec();
  authSocket = new QUdpSocket();
  authSocket->bind(QHostAddress::Any, _port);
  connect(authSocket, SIGNAL(readyRead()), this, SLOT(read()));
  emit this->ready();
}

void AuthSocket::run() { m_running = true; }
void AuthSocket::stop() { m_running = false; }
