#include <QApplication>
#include <QScreen>
#include "mainwindow.h"
#include "setsocketsettings.h"

int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN32
  // QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
  // QTextCodec::setCodecForLocale(codec);
#endif

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  // qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
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
  QNetworkInterface interface;
  if (argc < 2) {
    SetSocketSettings settings;
    font = settings.font();
    // qDebug() << "PixelSize" << font.pixelSize();
    font.setPixelSize(40);
    settings.setFont(font);

    qDebug() << "show\n";
    settings.show();

    if (settings.exec() != QDialog::Rejected) {
      loadMainWindow = true;
      nickname = settings.getNickname();
      port = settings.getPort();
      interface = settings.getInterface();
      emit settings.deleteLater();
    };
  }
  qDebug() << loadMainWindow;
  if (loadMainWindow) {
    if (nickname.count() == 0) nickname = "Batman";
    if (port < 80) port = 7010;
    MainWindow window(nickname, port);
    window.startSocket(nickname, port, interface);
    window.show();
    qDebug() << "exit";
    return a.exec();
  }
  return 0;
}
