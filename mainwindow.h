#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <arpa/inet.h>
#include <QDebug>
#include <QMainWindow>
#include <QThread>
#include "authsocket.h"
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

 private slots:
  void on_sendingButton_pressed();

  void on_TestButton_pressed();

  void on_sendMSGButton_released();

 signals:
  void TestButton_pressing();
  void TestButton_unpressing();
  void sendMSGClient(QString, qint8);

 private:
  Ui::MainWindow *ui;
  QThread sendThread;
  QThread getThread;
  QThread authTheard;
};

#endif  // MAINWINDOW_H
