#ifndef SOCKET_H
#define SOCKET_H

#include <QAbstractSocket>

class socket : public QAbstractSocket
{

public:
    socket(SocketType socketType = UnknownSocketType, QObject *parent = 0);
};

#endif // SOCKET_H
