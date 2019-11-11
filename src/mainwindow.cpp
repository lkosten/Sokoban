#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent), gameStatus(MAIN_MENU), menuStatus(MENU_PLAY)
{
    initFont();
    initMainMenuVector();
    LevelsList::GetList();

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
    qglClearColor(Qt::black); // Черный цвет фона

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setFixedSize(static_cast<int>(windowWidth), static_cast<int>(windowHeight));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    initTextures();

}

void MainWindow::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, static_cast<GLint>(nWidth), static_cast<GLint>(nHeight));
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, 1, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    qglColor(Qt::white);


    switch (gameStatus)
    {
    case MAIN_MENU:
        drawMainMenu();
        break;

    case LEVEL_SELECTION:
        drawLevelSelection();
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        break;
    }
}

void MainWindow::drawMainMenu()
{

    glEnable(GL_TEXTURE_2D);
    qglColor(Qt::darkMagenta);
    drawTexture(QRectF{650, 0, 150, 150}, 1);
    drawTexture(QRectF{650, 150, 150, 150}, 1);
    drawTexture(QRectF{650, 300, 150, 150}, 1);
    drawTexture(QRectF{650, 450, 150, 150}, 1);
    glDisable(GL_TEXTURE_2D);


    int y = 200;
    int x = 30;
    for (const auto &i : mainMenuItems)
    {
        if (menuStatus == i.first)
        {
            qglColor(QColor(128, 0, 128));
            //x = 400 - (fontSelected.pixelSize() * static_cast<int>(i.second.size() / 4));
            renderText(x, y, i.second.c_str(), fontSelected);
            qglColor(Qt::white);
        }
        else
        {
            qglColor(Qt::white);
            //x = 400 - (font.pixelSize() * static_cast<int>(i.second.size() / 4));
            renderText(x, y, i.second.c_str(), font);
        }
        y += 70;
    }
}
void MainWindow::drawLevelSelection()
{
    int y = 100;
    int x = 30;

    for (unsigned int i = 0; i < LevelsList::GetNumber(); ++i)
    {
        if (i == LevelsList::selectedLevel)
        {
            qglColor(QColor(128, 0, 128));
            renderText(x, y, LevelsList::GetFNameDir(i).first, fontSelected);
            qglColor(Qt::white);
        }
        else
        {
            qglColor(Qt::white);
            renderText(x, y, LevelsList::GetFNameDir(i).first, font);
            qglColor(Qt::white);
        }
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
        switch (menuStatus)
        {
        case MENU_EXIT:
            close();
            break;

        case MENU_PLAY:
            gameStatus = LEVEL_SELECTION;

            break;

        case MENU_SETTINGS:
            break;

        case MENU_STATISTICS:
            break;
        }
        if (menuStatus == MENU_EXIT) close();
        break;
    }

    updateGL();
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
void MainWindow::initTextures()
{

    glEnable(GL_TEXTURE_2D);
    QImage image;

    image.load(":/texture/brick_wall.png");
    textureID[Texture::WALL] = bindTexture(image);

    image.load(":/texture/barrel.png");
    textureID[Texture::BOX] = bindTexture(image);

    image.load(":/texture/circle.png");
    textureID[Texture::CIRCLE] = bindTexture(image);

    image.load(":/texture/skeleton.png");
    textureID[Texture::MAN] = bindTexture(image);


    image.load(":/texture/empty.png");
    textureID[Texture::EMPTY] = textureID[Texture::OUTSIDE] = bindTexture(image);

    glDisable(GL_TEXTURE_2D);
}

