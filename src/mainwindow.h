#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FLAGS.h"

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <vector>
#include <string>
#include <map>
#include <QtDebug>
#include <QMouseEvent>

#include "statusEnums.h"
#include "levelslist.h"
#include "levelhandler.h"
#include "leveldrawer.h"
#include "levellogic.h"
#include "levelcreator.h"
#include "levelcreatordrawer.h"

class MainWindow : public QGLWidget
{
    Q_OBJECT

protected:
    friend class LevelDrawer;
    friend class CreatorDrawer;
    friend class LevelCreator;

    const size_t windowHeight = 600, windowWidth = 800;
    const int windowPosX = 0, windowPosY = 0;
    GameStatus gameStatus;
    MainMenuStatus menuStatus;
    QFont font;
    QFont fontSelected;
    QFont fontSmall;
    std::vector<std::pair<MainMenuStatus, std::string>> mainMenuItems;
    std::vector<GLuint> textureManID;
    std::map<Texture, GLuint> textureID;

    bool mouseHold = false;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

    void initMainMenuVector();
    void initFont();
    void initTextures();

    void drawMainMenu();
    void drawLevelSelection();
    void keyMainMenu(QKeyEvent*);
    void keyLevelSelection(QKeyEvent*);
    void keyPlaying(QKeyEvent*);
    void keyCreating(QKeyEvent*);

    void mouseCreatin(QMouseEvent*);

public:
    MainWindow(QWidget *parent = nullptr);


};


#endif // MAINWINDOW_H
