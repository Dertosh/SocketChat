#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QDebug>
#include <QMainWindow>
#include <QTextCodec>
#include <QThread>
#include <QtDebug>
#include "myChatSocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  // void addText(QString);
  void on_sendMSGButton_released();

  void on_lineMessege_editingFinished();

 signals:
  void sendMSGClient(QString, qint8);

 private:
  Ui::MainWindow *ui;
  QThread chatTheard;
};

#endif  // MAINWINDOW_H
