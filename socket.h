#ifndef SOCKET_H
#define SOCKET_H

#include <QIODevice>
#include <QAbstractSocket>

class Socket : public QAbstractSocket
{

public:
    Socket(SocketType socketType = UnknownSocketType, QObject *parent = 0);
};

#endif // SOCKET_H
