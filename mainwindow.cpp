#include "mainwindow.h"
#include <QtDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  int id = 555;
  QString nickname = "Batman";
  quint16 _port = 7010;
  qDebug("nickname");
  QTextBrowser *mesgWindow = ui->mesgOut;
  //  Client *client = new Client(_port);
  //  client->moveToThread(&sendThread);
  //  connect(&sendThread, &QThread::finished, client, &QObject::deleteLater);
  //  connect(&sendThread, SIGNAL(started()), client, SLOT(doWork()));

  //  Server *server = new Server(_port);
  //  server->moveToThread(&getThread);
  //  connect(&getThread, &QThread::finished, server, &QObject::deleteLater);
  //  connect(&getThread, SIGNAL(started()), server, SLOT(doWork()));

  AuthSocket *authSocket = new AuthSocket(_port);
  authSocket->moveToThread(&authTheard);
  connect(this, SIGNAL(sendMSGClient(QString, qint8)), authSocket,
          SLOT(send(QString, qint8)));
  connect(&authTheard, SIGNAL(finished()), authSocket, SLOT(deleteLater()));
  connect(&authTheard, SIGNAL(finished()), authSocket, SLOT(stop()));
  connect(&authTheard, SIGNAL(started()), authSocket, SLOT(process()));
  // getThread.start();
  // sendThread.start();
  authTheard.start();
  qDebug() << "threads starts!";

  mesgWindow->append("Hellow world!");
  QString buff = "bindStatus = ";
  // buff.append((bindStatus + 1) * 10);
  QString answer = "No";
  if (sendThread.isRunning()) answer = "Yes";
  mesgWindow->append(answer);

  // while (mySocketGet->isReadable()) {
  // mySocketGet->open(QIODevice::ReadOnly);
  // mySocketGet->readyRead();
  int t = 'А';
  mesgWindow->append("Port: " + QString::number(_port));
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
  // connect(this, SIGNAL(TestButton_pressing()), server, SLOT(getMSG()));
  // connect(this, SIGNAL(TestButton_pressing()), server, SLOT(setSending()));
  // connect(this, SIGNAL(TestButton_unpressing()), server, SLOT(setEnding()));
}

MainWindow::~MainWindow() {
  qDebug() << "close window";
  delete ui;
  sendThread.quit();
  getThread.quit();
  authTheard.quit();
  sendThread.wait();
  getThread.wait();
  authTheard.wait();
}

void MainWindow::on_sendingButton_pressed() {
  if (ui->sendingButton->isChecked())
    ui->sendingButton->setText("Отправить сообщения");
  else
    ui->sendingButton->setText("Отправка сообщений");
}

void MainWindow::on_TestButton_pressed() {
  if (ui->TestButton->isChecked()) {
    TestButton_unpressing();
    qDebug() << "TestButton_unpressing();";
    ui->TestButton->setText("Прочитать сообщения");
  } else {
    TestButton_pressing();
    qDebug() << "TestButton_pressing()";
    ui->TestButton->setText("Чтение сообщений");
  }
}

void MainWindow::on_sendMSGButton_released() {
  sendMSGClient(ui->lineMessege->text(), 1);
  ui->lineMessege->clear();
}
