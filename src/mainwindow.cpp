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
    qglClearColor(Qt::black); // Черный цвет фона

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setFixedSize(windowWidth, windowHeight);
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

    glEnable(GL_TEXTURE_2D);
    qglColor(QColor(128, 0, 128));
    drawTexture(QRectF{0, 0, 128, 128}, 0);
    drawTexture(QRectF{0, 128, 128, 128}, 1);
    drawTexture(QRectF{128, 128, 128, 128}, 3);
    qglColor(Qt::white);
    drawTexture(QRectF{128, 0, 128, 128}, 4);
    drawTexture(QRectF{128, 128, 128, 128}, 2);
    glDisable(GL_TEXTURE_2D);


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
            qglColor(QColor(128, 0, 128));
            x = 400 - (fontSelected.pixelSize() * static_cast<int>(i.second.size() / 4));
            renderText(x, y, i.second.c_str(), fontSelected);
            qglColor(Qt::white);
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

