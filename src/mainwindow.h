#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <vector>
#include <string>
#include <map>

#include "statusEnums.h"
#include "levelslist.h"

class MainWindow : public QGLWidget
{
    Q_OBJECT

protected:
    friend class LevelDrawer;

    const size_t windowHeight = 600, windowWidth = 800;
    const int windowPosX = 0, windowPosY = 0;
    GameStatus gameStatus;
    MainMenuStatus menuStatus;
    QFont font;
    QFont fontSelected;
    std::vector<std::pair<MainMenuStatus, std::string>> mainMenuItems;
    std::map<Texture, GLuint> textureID;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyReleaseEvent(QKeyEvent*) override;

    void initMainMenuVector();
    void initFont();
    void initTextures();

    void drawMainMenu();
    void drawLevelSelection();
    void keyMainMenu(QKeyEvent*);

public:
    MainWindow(QWidget *parent = nullptr);


};


#endif // MAINWINDOW_H
