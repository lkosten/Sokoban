#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    show();
}

void MainWindow::initializeGL()
{
    qglClearColor(Qt::darkRed);
    setGeometry(windowPosX, windowPosY, windowWidth, windowHeidht);
    setWindowTitle("Sokoban");
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    show();
}

void MainWindow::resizeGL(int, int){}

void MainWindow::paintGL()
{

}
