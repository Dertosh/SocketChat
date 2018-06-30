#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QLoggingCategory>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include "nativesocket.h"
#include "socket.h"
Q_DECLARE_LOGGING_CATEGORY(logCategoryServer)

class Server : public QTcpServer {
  Q_OBJECT
 public:
  explicit Server(size_t = 0);
  ~Server();

 signals:
  void ending();
  void finished();
  void error(QString err);

 public slots:
  void doWork();
  void read();
  void setEnding(bool status);
  void setEnding();
  void setSending();

 private:
  quint16 _port = 0;
  QTcpServer *serverSocket = nullptr;
  QUdpSocket *authSocket = nullptr;
  bool statusRead = false;
  QHash<QTcpSocket *, QByteArray *>
      buffers;  // We need a buffer to store data until block has completely
                // received
  QHash<QTcpSocket *, qint32 *> sizes;  // We need to store the size to verify
                                        // if a block has received completely
};

#endif  // SERVER_H
