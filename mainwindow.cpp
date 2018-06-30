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

  myChat *authSocket = new myChat(_port);
  authSocket->moveToThread(&authTheard);
  connect(this, SIGNAL(sendMSGClient(QString, qint8)), authSocket,
          SLOT(send(QString, qint8)));
  connect(&authTheard, SIGNAL(finished()), authSocket, SLOT(deleteLater()));
  connect(&authTheard, SIGNAL(finished()), authSocket, SLOT(stop()));
  connect(&authTheard, SIGNAL(started()), authSocket, SLOT(process()));
  connect(authSocket, SIGNAL(showMSG(QString)), ui->mesgOut,
          SLOT(append(QString)));

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

void MainWindow::addText(QString text) {}

void MainWindow::on_lineMessege_editingFinished() {
  if (ui->lineMessege->text().count() > 0) {
    sendMSGClient(ui->lineMessege->text(), 1);
    ui->lineMessege->clear();
  }
}
