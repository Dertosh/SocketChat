#include <QApplication>
#include <QScreen>
#include "mainwindow.h"
#include "setsocketsettings.h"
void test_function();

int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN32
  QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
  QTextCodec::setCodecForLocale(codec);
#endif

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
  QApplication a(argc, argv);
  qDebug() << qApp->primaryScreen()->devicePixelRatio();
  qDebug() << qApp->primaryScreen()->logicalDotsPerInch();
  QFont font = qApp->font();
  qDebug() << "PixelSize" << font.pixelSize();
  font.setPixelSize(1);
  // font.setPixelSize(qApp->primaryScreen()->logicalDotsPerInch() /
  //                  (qApp->primaryScreen()->devicePixelRatio()));
  qApp->setFont(font);

  qDebug() << "argc =" << argc << "argv" << *argv;

  bool loadMainWindow = true;
  MainWindow window;
  if (argc < 2) {
    qDebug() << "show";
    SetSocketSettings settings;
    font = settings.font();
    qDebug() << "PixelSize" << font.pixelSize();
    font.setPixelSize(40);
    settings.setFont(font);

    QObject::connect(&settings, SIGNAL(accepted()), &window, SLOT(show()));
    QObject::connect(&settings, SIGNAL(rejected()), &window,
                     SLOT(deleteLater()));
    settings.show();
    settings.exec();
  }

  return a.exec();
}
