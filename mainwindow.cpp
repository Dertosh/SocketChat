#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) { MainWindow("Batman", 7010, parent); }

MainWindow::MainWindow(QString nickname, quint16 port, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  qDebug() << "close window";
  chatTheard.quit();
  delete ui;
  chatTheard.wait();
}

void MainWindow::on_sendMSGButton_released() {
  if (ui->lineMessege->text().count() > 0) {
    QString temp = ui->lineMessege->text();
    ui->lineMessege->clear();
    sendMSGClient(temp, 1);
  }
}

void MainWindow::on_lineMessege_editingFinished() {
  if (ui->lineMessege->text().count() > 0) {
    QString temp = ui->lineMessege->text();
    ui->lineMessege->clear();
    sendMSGClient(temp, 1);
  }
}

void MainWindow::printMSG(QString sender, QString text) {
  if (QString::compare(sender, nickname, Qt::CaseInsensitive) == 0) {
    ui->mesgOut->append("<font color=\"Green\">" + sender + ": </font>" + text);
    ui->mesgOut->setAlignment(Qt::AlignRight);
  } else {
    ui->mesgOut->append("<font color=\"DarkBlue\">" + sender + ": </font>" +
                        text);
    ui->mesgOut->setAlignment(Qt::AlignLeft);
  }
}

void MainWindow::startSocket(QString nickname, quint16 port,
                             QNetworkInterface &interface) {
  this->nickname = nickname;

  myChat *chatSocket = new myChat(nickname, port, interface);

  chatSocket->moveToThread(&chatTheard);
  QThread::connect(this, SIGNAL(sendMSGClient(QString, qint8)), chatSocket,
                   SLOT(send(QString, qint8)));
  QThread::connect(&chatTheard, SIGNAL(finished()), chatSocket,
                   SLOT(deleteLater()));
  QThread::connect(&chatTheard, SIGNAL(finished()), chatSocket, SLOT(stop()));
  QThread::connect(&chatTheard, SIGNAL(started()), chatSocket, SLOT(process()));
  QThread::connect(chatSocket, SIGNAL(showMSG(QString, QString)), this,
                   SLOT(printMSG(QString, QString)));
  QThread::connect(this, SIGNAL(destroyed()), &chatTheard, SLOT(deleteLater()));

  chatTheard.start();

  ui->mesgOut->insertHtml(
      " <meta content=\"text/html; charset=utf-8\" "
      "http-equiv=\"Content-Type\"><div align=\"center\">" +
      QString::fromLocal8Bit("Сокет чата запущен на порту: ") +
      QString::number(port) + "</div><br>");

  qDebug() << "threads starts!";
}
