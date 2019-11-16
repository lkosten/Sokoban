#ifndef LEVELDRAWER_H
#define LEVELDRAWER_H
#include "FLAGS.h"
#include "mainwindow.h"
#include "levelhandler.h"

class MainWindow;

class LevelDrawer
{
private:
    static const size_t protectedAreaY = 200;
    static const size_t protectedAreaX = 100;


public:
    static void fullRender(MainWindow&);


};

#endif // LEVELDRAWER_H
