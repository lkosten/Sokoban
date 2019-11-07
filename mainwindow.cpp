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
    setWindowTitle("Sokoban");
    setGeometry(100, 100, 0, 0);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setFixedSize(windowWidth, windowHeidht);

    show();
}

void MainWindow::resizeGL(int, int){}

void MainWindow::paintGL()
{

}
