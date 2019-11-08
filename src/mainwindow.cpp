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
}

void MainWindow::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(0,windowWidth,windowHeight,0,1,0); // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        qglColor(Qt::white);

    glEnable(GL_TEXTURE_2D);
    QImage image;
    bool ok = image.load(":/texture/brick_wall.png");
    if (!ok) close();


     qglColor(QColor(128, 0, 128));
    drawTexture(QRectF{0, 0, 40, 40}, bindTexture(image));
    drawTexture(QRectF{0, 40, 40, 40}, 1);
    drawTexture(QRectF{40, 0, 40, 40}, 1);
    drawTexture(QRectF{40, 40, 40, 40}, 1);
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

