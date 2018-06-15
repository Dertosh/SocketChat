#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <arpa/inet.h>
#include <QDebug>
#include <QMainWindow>
#include <QThread>
#include "client.h"
#include "server.h"
#include "socket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QThread sendThread;
  QThread getThread;
};

#endif  // MAINWINDOW_H
