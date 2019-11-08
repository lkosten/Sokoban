#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent), gameStatus(MAIN_MENU), menuStatus(MENU_PLAY)
{
    initFont();
    initMainMenuVector();
    show();
}

void MainWindow::keyReleaseEvent(QKeyEvent *key)
{
    switch (gameStatus)
    {
    case MAIN_MENU:
        keyMainMenu(key);
        break;

    case LEVEL_SELECTION:
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        break;
    }
    updateGL();
}

void MainWindow::initializeGL()
{
    setWindowTitle("Sokoban");
    setGeometry(100, 100, 0, 0);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setFixedSize(windowWidth, windowHeidht);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void MainWindow::resizeGL(int, int){}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
    //glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    //glLoadIdentity();           // загрузка единичную матрицу

    switch (gameStatus)
    {
    case MAIN_MENU:
        drawMainMenu();
        break;

    case LEVEL_SELECTION:
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        break;
    }
}

void MainWindow::drawMainMenu()
{
    int y = 200;
    int x = 300;
    for (const auto &i : mainMenuItems)
    {
        if (menuStatus == i.first)
        {
            qglColor(QColor(245, 140, 25));
            x = 400 - (fontSelected.pixelSize() * static_cast<int>(i.second.size() / 4));
            renderText(x, y, i.second.c_str(), fontSelected);
        }
        else
        {
            qglColor(Qt::white);
            x = 400 - (font.pixelSize() * static_cast<int>(i.second.size() / 4));
            renderText(x, y, i.second.c_str(), font);
        }
        y += 70;
    }
}
void MainWindow::keyMainMenu(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Up:
        if (menuStatus != MENU_PLAY)
        {
            menuStatus = static_cast<MainMenuStatus>(static_cast<int>(menuStatus) - 1);
        }
        break;

    case Qt::Key_Down:
        if (menuStatus != MENU_EXIT)
        {
            menuStatus = static_cast<MainMenuStatus>(static_cast<int>(menuStatus) + 1);
        }
        break;

    case Qt::Key_Return:
        if (menuStatus == MENU_EXIT) close();
        break;
    }
}
void MainWindow::initMainMenuVector()
{
    mainMenuItems.emplace_back(MENU_PLAY, "Play");
    mainMenuItems.emplace_back(MENU_STATISTICS, "Statistics");
    mainMenuItems.emplace_back(MENU_SETTINGS, "Settings");
    mainMenuItems.emplace_back(MENU_EXIT, "Exit");
}
void MainWindow::initFont()
{
    font.setPixelSize(50);
    font.setStyleHint(QFont::OldEnglish);

    fontSelected.setPixelSize(60);
    fontSelected.setStyleHint(QFont::OldEnglish);
}

