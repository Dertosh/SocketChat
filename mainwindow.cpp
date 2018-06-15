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
  Client *client = new Client(_port);
  client->moveToThread(&sendThread);
  connect(&sendThread, &QThread::finished, client, &QObject::deleteLater);
  connect(&sendThread, SIGNAL(started()), client, SLOT(doWork()));

  Server *server = new Server(nullptr, _port);
  server->moveToThread(&getThread);
  connect(&getThread, &QThread::finished, server, &QObject::deleteLater);
  connect(&getThread, SIGNAL(started()), server, SLOT(doWork()));

  sendThread.start();
  getThread.start();

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
  mesgWindow->append(QString::number(t));
  QString test = QString::fromLocal8Bit("Почему не работает передача?");
}

MainWindow::~MainWindow() {
  qDebug() << "test!";
  delete ui;
  sendThread.quit();
  getThread.quit();
  sendThread.wait();
  getThread.wait();
}
