#include "mainwindow.h"
#include "levelslist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    LevelsList test;

    QApplication a(argc, argv);
    MainWindow window;
    return a.exec();
}
