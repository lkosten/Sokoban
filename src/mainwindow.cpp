#include "mainwindow.h"
#include "QLineEdit"


const QColor FLAGS::wallColor      = Qt::darkMagenta;
const QColor FLAGS::outsideColor   = Qt::white;
const QColor FLAGS::emptyColor     = Qt::white;
const QColor FLAGS::manColor       = Qt::white;
const QColor FLAGS::boxColor       = Qt::yellow;
const QColor FLAGS::pointColor     = Qt::red;
const QColor FLAGS::circleBoxColor = Qt::green;
const QColor FLAGS::spawnColor     = Qt::white;
const QColor FLAGS::eraserColor    = Qt::blue;
const QColor FLAGS::frameColor     = Qt::white;

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent), gameStatus(MAIN_MENU), menuStatus(MENU_PLAY)
{
    initFont();
    initMainMenuVector();
    LevelsList::GetList();
    ColorPallete::init( 0 , 0 , 300 , 4);
    show();
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
   switch (gameStatus)
    {
    case MAIN_MENU:
        keyMainMenu(key);
        break;

    case LEVEL_SELECTION:
        keyLevelSelection(key);
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        break;

    case PLAYING:
        keyPlaying(key);
        break;

    case LEVEL_CREATOR:
        keyCreating(key);
        break;

   case LEVEL_COMPLETED:
       gameStatus = LEVEL_SELECTION;
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
        ColorPallete::draw(*this);
        break;

    case LEVEL_SELECTION:
        drawLevelSelection();
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        break;

    case PLAYING:
        LevelDrawer::fullRender(*this);
        break;

    case LEVEL_CREATOR:
        CreatorDrawer::fullRender(*this);
        break;

    case LEVEL_COMPLETED:
        LevelDrawer::fullRender(*this);
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


    int y = 165;
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
    glEnable(GL_TEXTURE_2D);
    qglColor(Qt::red);
    drawTexture(QRectF{650, 0, 150, 150}, 1);
    drawTexture(QRectF{650, 150, 150, 150}, 1);
    drawTexture(QRectF{650, 300, 150, 150}, 1);
    drawTexture(QRectF{650, 450, 150, 150}, 1);
    glDisable(GL_TEXTURE_2D);
    int y = 100;
    int x = 30;

    for (unsigned int i = LevelsList::minPrintedLevel; i <= LevelsList::maxPrintedLevel; ++i)
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
        else
        {
            menuStatus = MENU_EXIT;
        }
        break;

    case Qt::Key_Down:
        if (menuStatus != MENU_EXIT)
        {
            menuStatus = static_cast<MainMenuStatus>(static_cast<int>(menuStatus) + 1);
        }
        else
        {
            menuStatus = MENU_PLAY;
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

        case MENU_LEVEL_CREATOR:
            gameStatus = LEVEL_CREATOR;
            LevelCreator::initMap();
            break;
        }
        break;

    case Qt::Key_Escape:
        close();

    }

    updateGL();
}

static QString newfilename("newlevel");
void MainWindow::keyCreating(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Up:
        LevelCreator::KeyUp();
        break;

    case Qt::Key_Down:
        LevelCreator::KeyDown();
        break;

    case Qt::Key_Return:
        LevelCreator::Write(newfilename);
        break;
    case Qt::Key_Escape:
        LevelCreator::clear();
        gameStatus = MAIN_MENU;
        break;
    }

    updateGL();
}

void MainWindow::keyLevelSelection(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Up:
        if (LevelsList::selectedLevel != 0)
        {
            if (LevelsList::selectedLevel == LevelsList::minPrintedLevel)
            {
                --LevelsList::minPrintedLevel;
                --LevelsList::maxPrintedLevel;
            }
            --LevelsList::selectedLevel;
        }
        else
        {
            LevelsList::selectedLevel = LevelsList::GetNumber() - 1;
            LevelsList::maxPrintedLevel = LevelsList::GetNumber() - 1;
            LevelsList::minPrintedLevel = LevelsList::GetNumber() - 7;
        }
        break;

    case Qt::Key_Down:
        if (LevelsList::selectedLevel != LevelsList::GetNumber() - 1)
        {
            if (LevelsList::selectedLevel == LevelsList::maxPrintedLevel)
            {
             ++LevelsList::minPrintedLevel;
             ++LevelsList::maxPrintedLevel;
            }
            ++LevelsList::selectedLevel;
        }
        else
        {
            LevelsList::selectedLevel = 0;
            LevelsList::maxPrintedLevel = 6;
            LevelsList::minPrintedLevel = 0;
        }
        break;

    case Qt::Key_Return:
        LevelHandler::read(LevelsList::GetFNameDir(static_cast<unsigned int>(LevelsList::selectedLevel)).second);
        gameStatus = PLAYING;
        break;

    case Qt::Key_Escape:
        gameStatus = MAIN_MENU;
        break;
    }

    updateGL();
}
void MainWindow::keyPlaying(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Up:
        LevelLogic::MoveUp();
        break;

    case Qt::Key_Down:
        LevelLogic::MoveDown();
        break;

    case Qt::Key_Right:
        LevelLogic::MoveRight();
        break;

    case Qt::Key_Left:
        LevelLogic::MoveLeft();
        break;
    case Qt::Key_R:
        LevelHandler::read(LevelsList::GetFNameDir(static_cast<unsigned int>(LevelsList::selectedLevel)).second);
        break;
    case Qt::Key_Escape:
        gameStatus = LEVEL_SELECTION;
    }
    qDebug() << LevelLogic::GetCorrectNumber() << LevelLogic::GetTotalNumber();
    updateGL();
}
void MainWindow::initMainMenuVector()
{
    mainMenuItems.emplace_back(MENU_PLAY, "Play");
    mainMenuItems.emplace_back(MENU_LEVEL_CREATOR, "Level creator");
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

    fontSmall.setPixelSize(30);
    fontSmall.setStyleHint(QFont::OldEnglish);
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

    image.load(":/texture/rubber.png");
    textureID[Texture::ERASER] = bindTexture(image);

    image.load(":/texture/round_star.png");
    textureID[Texture::SPAWNPOINT] = bindTexture(image);

    image.load(":/texture/empty.png");
    textureID[Texture::EMPTY] = textureID[Texture::OUTSIDE] = bindTexture(image);

    image.load(":/texture/frame.png");
    textureID[Texture::FRAME] = bindTexture(image);

    image.load(":/texture/plus.png");
    textureID[Texture::PLUS] = bindTexture(image);

    image.load(":/texture/minus.png");
    textureID[Texture::MINUS] = bindTexture(image);

    image.load(":/texture/dot.png");
    textureID[Texture::DOT] = bindTexture(image);

    glDisable(GL_TEXTURE_2D);
}

void MainWindow::mousePressEvent(QMouseEvent *mouse){
    mouseHold = true;
    ColorPallete::Click(mouse->x(), mouse->y());
    switch (gameStatus)
    {
    case MAIN_MENU:
        break;

    case LEVEL_SELECTION:
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        break;

    case PLAYING:
        break;

    case LEVEL_CREATOR:
        LevelCreator::MouseClicked(mouse->x(), mouse->y());
        break;

    case LEVEL_COMPLETED:
        break;
    }
    updateGL();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *mouse){
    mouseHold = false;
    ColorPallete::Release();
}
void MainWindow::mouseMoveEvent(QMouseEvent *mouse){
    if(mouseHold){
        ColorPallete::Hold(mouse->y());
        updateGL();
    }
}
