#ifndef SOCKET_H
#define SOCKET_H

#include <QIODevice>
#include <QAbstractSocket>

class Socket : public QAbstractSocket
{

public:
    enum SocketType {
        TcpSocket,
        UdpSocket,
        SctpSocket,
        MySocket,
        UnknownSocketType = -1
    };
    Q_ENUM(SocketType)

    Socket(SocketType socketType = MySocket, QObject *parent = nullptr);
};

#endif // SOCKET_H
