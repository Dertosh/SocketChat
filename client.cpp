#include "client.h"
Q_LOGGING_CATEGORY(logCategoryClient, "Client")

Client::Client(int port) { _port = port; }
Client::~Client() {
  clientSocket->disconnectFromHost();
  authSocket->disconnectFromHost();
  clientSocket->close();
  authSocket->close();
  qDebug() << "Disconnect " << clientSocket->waitForDisconnected(1000);
  delete clientSocket;
  qDebug("Client: Exit");
}

void Client::doWork() {
  // NativeSocket* sok = new NativeSocket();
  // sok->connectToHost(SO_REUSEADDR | SO_REUSEPORT, 1, uint16_t(8080));
  if (clientSocket != NULL) return;
  clientSocket = new QTcpSocket();
  authSocket = new QUdpSocket();
  // mySocketSend->connectToHost("127.0.0.1", _port);
  QThread::sleep(1);
  // authSocket->connectToHost(QHostAddress::Broadcast, _port);
  qDebug() << "Client: conection" << authSocket->waitForConnected();
}

void Client::setStatusSending(bool status) {
  qDebug() << "status -" << status;
  statusSend = status;
  if (status == true) isSending();
}

void Client::sending(QString str, qint8 typeMSG) {
  qDebug(logCategoryClient()) << "Sending";
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << qint64(0);
  out << qint8(typeMSG);
  out << str;
  out.device()->seek(qint64(0));
  out << qint64(data.size() - sizeof(qint64));
  authSocket->writeDatagram(data, QHostAddress::Broadcast, _port);
}
