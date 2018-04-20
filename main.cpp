#include "mainwindow.h"
#include <QApplication>

void test_function();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return a.exec();
}

void test_function()
{

}
