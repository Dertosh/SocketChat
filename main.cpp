﻿#include <QApplication>
#include <QScreen>
#include "mainwindow.h"
#include "setsocketsettings.h"

int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN32
  QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
  QTextCodec::setCodecForLocale(codec);
#endif

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
  QApplication a(argc, argv);
  // qDebug() << qApp->primaryScreen()->devicePixelRatio();
  // qDebug() << qApp->primaryScreen()->logicalDotsPerInch();
  QFont font = qApp->font();
  // qDebug() << "PixelSize" << font.pixelSize();
  font.setPixelSize(1);
  // font.setPixelSize(qApp->primaryScreen()->logicalDotsPerInch() /
  //                  (qApp->primaryScreen()->devicePixelRatio()));
  qApp->setFont(font);

  qDebug() << "argc =" << argc << "argv" << *argv;

  bool loadMainWindow = false;
  QString nickname = "Batman";
  quint16 port = 7010;
  if (argc < 2) {
    qDebug() << "show\n";
    SetSocketSettings settings;
    font = settings.font();
    // qDebug() << "PixelSize" << font.pixelSize();
    font.setPixelSize(40);
    settings.setFont(font);

    // QObject::connect(&settings, SIGNAL(accepted()), &window, SLOT(show()));
    // QObject::connect(&settings, SIGNAL(rejected()), &window,
    //                 SLOT(deleteLater()));
    settings.show();
    // qDebug() << "settings.exec() =" << settings.exec();
    if (settings.exec() != QDialog::Rejected) {
      loadMainWindow = true;
      nickname = settings.getNickname();
      port = settings.getPort();
    };
  }
  qDebug() << loadMainWindow;
  if (loadMainWindow) {
    MainWindow window(nickname, port);
    window.show();
    return a.exec();
  }
  return 0;
}
