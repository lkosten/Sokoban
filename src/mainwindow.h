#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <vector>
#include <string>
#include "statusEnums.h"

class MainWindow : public QGLWidget
{
    Q_OBJECT

protected:
    const int windowHeidht = 600, windowWidth = 800;
    const int windowPosX = 200, windowPosY = 200;
    GameStatus gameStatus;
    MainMenuStatus menuStatus;
    QFont font;
    QFont fontSelected;
    std::vector<std::pair<MainMenuStatus, std::string>> mainMenuItems;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyReleaseEvent(QKeyEvent*) override;

    void initMainMenuVector();
    void initFont();

    void drawMainMenu();
    void keyMainMenu(QKeyEvent*);

public:
    MainWindow(QWidget *parent = nullptr);


};


#endif // MAINWINDOW_H
