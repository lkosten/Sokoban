#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QGLWidget
{
    Q_OBJECT

protected:
    const int windowHeidht = 600, windowWidth = 800;
    const int windowPosX = 200, windowPosY = 200;
    GameStatus
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


public:
    MainWindow(QWidget *parent = nullptr);


};


#endif // MAINWINDOW_H
