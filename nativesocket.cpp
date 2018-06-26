#include "nativesocket.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

NativeSocket::NativeSocket(QObject *parent) : QObject(parent) {
  _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
}

bool NativeSocket::connectToHost(int openMode, int size, uint16_t port) {
  char buffer[1024] = {0};
  char *hello = "Hello from server";
  int addrlen = sizeof(_address);
  int opt = 1;
  // Forcefully attaching socket to the port 8080
  if (setsockopt(_socket_fd, SOL_SOCKET, openMode, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  _address.sin_family = AF_INET;
  _address.sin_addr.s_addr = INADDR_ANY;
  _address.sin_port = htons(8080);

  // Forcefully attaching socket to the port 8080
  if (bind(_socket_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  //  if (listen(_socket_fd, 3) < 0) {
  //    perror("listen");
  //    exit(EXIT_FAILURE);
  //  }
  //  if ((_new_socket = accept(_socket_fd, (struct sockaddr *)&_address,
  //                            (socklen_t *)&addrlen)) < 0) {
  //    perror("accept");
  //    exit(EXIT_FAILURE);
  //  }
  qDebug() << "send test = " << send(_socket_fd, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  return true;
}

int NativeSocket::sendMSG() {
  struct sockaddr_in address;
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char *hello = "Hello from client";
  qDebug() << hello;
  char buffer[1024] = {0};
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  //  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
  //    printf("\nConnection Failed \n");
  //    return -1;
  //  }
  send(sock, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  // valread = read(sock, buffer, 1024);
  // printf("%s\n", buffer);
  return 0;
}
