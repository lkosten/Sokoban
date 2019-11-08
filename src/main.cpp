#include "mainwindow.h"
#include "levelslist.h"

#include <QApplication>
#include <QtDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    return a.exec();
}
