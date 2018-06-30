#include "mainwindow.h"
#include <QtDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QString nickname = "Batman";
  quint16 _port = 7010;
  qDebug("nickname");
  QTextBrowser *mesgWindow = ui->mesgOut;

  myChat *chatSocket = new myChat(_port);
  chatSocket->moveToThread(&authTheard);
  connect(this, SIGNAL(sendMSGClient(QString, qint8)), chatSocket,
          SLOT(send(QString, qint8)));
  connect(&authTheard, SIGNAL(finished()), chatSocket, SLOT(deleteLater()));
  connect(&authTheard, SIGNAL(finished()), chatSocket, SLOT(stop()));
  connect(&authTheard, SIGNAL(started()), chatSocket, SLOT(process()));
  connect(chatSocket, SIGNAL(showMSG(QString)), ui->mesgOut,
          SLOT(append(QString)));
  connect(chatSocket, SIGNAL(showMSG(QString)), ui->mesgOut, SLOT(app));

  authTheard.start();
  qDebug() << "threads starts!";

  mesgWindow->append("Hellow world!");
  mesgWindow->append("Port: " + QString::number(_port));
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
}

MainWindow::~MainWindow() {
  qDebug() << "close window";
  delete ui;
  authTheard.quit();
  authTheard.wait();
}

void MainWindow::on_sendMSGButton_released() {
  if (ui->lineMessege->text().count() > 0) {
    sendMSGClient(ui->lineMessege->text(), 1);
    ui->lineMessege->clear();
  }
}

// void MainWindow::addText(QString text) {}

void MainWindow::on_lineMessege_editingFinished() {
  if (ui->lineMessege->text().count() > 0) {
    sendMSGClient(ui->lineMessege->text(), 1);
    ui->lineMessege->clear();
  }
}
