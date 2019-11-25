#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FLAGS.h"

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QtMultimedia/QAudio>
#include <vector>
#include <string>
#include <map>
#include <QtDebug>
#include <QMediaPlayer>
#include <QAudio>
#include <regex>
#include <stack>
#include <ctime>

#include "statusEnums.h"
#include "levelslist.h"
#include "levelhandler.h"
#include "leveldrawer.h"
#include "levellogic.h"
#include "levelcreator.h"
#include "levelcreatordrawer.h"
#include "ColorPallete.h"


class MainWindow : public QGLWidget
{
    Q_OBJECT

protected:
    friend class LevelDrawer;
    friend class CreatorDrawer;
    friend class LevelCreator;
    friend class ColorPallete;

    bool mouseHold = false;
    const size_t windowHeight = 600, windowWidth = 800;
    const int windowPosX = 0, windowPosY = 0;
    size_t textureManIndex = 0;
    GameStatus gameStatus;
    MainMenuStatus menuStatus;
    QFont font;
    QFont fontSelected;
    QFont fontSmall;
    std::vector<std::pair<MainMenuStatus, std::string>> mainMenuItems;
    std::vector<GLuint> textureManID;
    std::map<Texture, GLuint> textureID;

    static QMediaPlayer mediaPlayer;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

    void initMainMenuVector();
    void initFont();
    void initTextures();
    void initColors();

    void saveColors();

    void drawMainMenu();
    void drawLevelSelection();
    void drawSettings();
    void drawStatistics();

    void keyMainMenu(QKeyEvent*);
    void keyLevelSelection(QKeyEvent*);
    void keyPlaying(QKeyEvent*);
    void keyCreating(QKeyEvent*);
    void keySettings(QKeyEvent*);
    void keyStatistics(QKeyEvent*);

    void mouseCreatin(QMouseEvent*);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

};


#endif // MAINWINDOW_H
