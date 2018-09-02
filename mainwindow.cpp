#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) { MainWindow("Batman", 7010, parent); }

MainWindow::MainWindow(QString nickname, quint16 port, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  if (nickname.count() == 0) nickname = "Batman";
  if (port < 80) port = 7010;
  QTextBrowser *mesgWindow = ui->mesgOut;
  myChat *chatSocket = new myChat(nickname, port);
  chatSocket->moveToThread(&chatTheard);
  connect(this, SIGNAL(sendMSGClient(QString, qint8)), chatSocket,
          SLOT(send(QString, qint8)));
  connect(&chatTheard, SIGNAL(finished()), chatSocket, SLOT(deleteLater()));
  connect(&chatTheard, SIGNAL(finished()), chatSocket, SLOT(stop()));
  connect(&chatTheard, SIGNAL(started()), chatSocket, SLOT(process()));
  connect(chatSocket, SIGNAL(showMSG(QString)), ui->mesgOut,
          SLOT(append(QString)));
  // connect(chatSocket, SIGNAL(showMSG(QString)), ui->mesgOut, SLOT(app));

  chatTheard.start();
  qDebug() << "threads starts!";

  QString helloMSGport =
      QString::fromLocal8Bit("Сокет чата запущен на порту: ");
  // mesgWindow->append("<div align=\"center\"><green>" + helloMSGport +
  //                   QString::number(_port) + "</green></div>");
  mesgWindow->insertHtml("<div align=\"center\"><green>" + helloMSGport +
                         QString::number(port) + "</green></div><br>");
}

MainWindow::~MainWindow() {
  qDebug() << "close window";
  delete ui;
  chatTheard.quit();
  chatTheard.wait();
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
