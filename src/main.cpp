#include "mainwindow.h"
#include "levelhandler.h"

#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    return a.exec();
}
