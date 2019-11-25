#include "mainwindow.h"
#include "QLineEdit"

QColor FLAGS::wallColor      = Qt::darkMagenta;
QColor FLAGS::outsideColor   = Qt::white;
QColor FLAGS::emptyColor     = Qt::white;
QColor FLAGS::manColor       = Qt::white;
QColor FLAGS::boxColor       = Qt::yellow;
QColor FLAGS::pointColor     = Qt::red;
QColor FLAGS::circleBoxColor = Qt::green;
QColor FLAGS::spawnColor     = Qt::white;
QColor FLAGS::eraserColor    = Qt::blue;
QColor FLAGS::frameColor     = Qt::white;

QMediaPlayer MainWindow::mediaPlayer;

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent), gameStatus(MAIN_MENU), menuStatus(MENU_PLAY)
{
    MainWindow::mediaPlayer.setMedia(QUrl("qrc:/music/maintheme.mp3"));
    MainWindow::mediaPlayer.setVolume(20);
    MainWindow::mediaPlayer.play();
    initFont();
    srand( time( 0 ) );
    initMainMenuVector();
    initColors();
    LevelsList::GetList();
    Stat::read();
    show();

}

MainWindow::~MainWindow()
{
    Stat::write();
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
       keyStatistics(key);
       break;

    case SETTINGS:
       keySettings(key);
       break;

    case PLAYING:
       keyPlaying(key);
       break;

    case LEVEL_CREATOR:
       keyCreating(key);
       break;

   case LEVEL_COMPLETED:
      if (key->key() == Qt::Key_Space) gameStatus = LEVEL_SELECTION;
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
        drawStatistics();
        break;

    case SETTINGS:
        drawSettings();
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
    qglColor(QColor(200, 55, 90));
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
            qglColor(QColor(200, 55, 90));
            renderText(x, y, LevelsList::GetFNameDir(i).first, fontSelected);
            qglColor(Qt::white);
        }
        else
        {
            qglColor(Qt::white);
            renderText(x, y, LevelsList::GetFNameDir(i).first, font);
        }
        y += 70;
    }
}
void MainWindow::drawSettings()
{
    const qreal blockSize = 200;
    const qreal delta = 50;

    ColorPallete::draw(*this);

    glEnable(GL_TEXTURE_2D);

    qglColor(ColorPallete::GetColor());
    drawTexture(QRectF{200, 350, blockSize, blockSize},
                textureManID[(textureManIndex + textureManID.size())
                % textureManID.size()]);


    qreal curX = delta, curY = delta;


    qglColor(FLAGS::manColor);
    drawTexture(QRectF{curX, curY, blockSize, blockSize},
                textureManID[(textureManIndex + textureManID.size() - 1)
                % textureManID.size()]);

    curX += blockSize + delta;
    drawTexture(QRectF{curX, curY, blockSize, blockSize},
                textureManID[(textureManIndex + textureManID.size())
                % textureManID.size()]);

    qglColor(Qt::white);
    drawTexture(QRectF{curX - 10, curY - 10, blockSize + 20, blockSize + 20},
                textureID[Texture::FRAME]);

    qglColor(FLAGS::manColor);
    curX += blockSize + delta;
    drawTexture(QRectF{curX, curY, blockSize, blockSize},
                textureManID[(textureManIndex + textureManID.size() + 1)
                % textureManID.size()]);

    glDisable(GL_TEXTURE_2D);
}
void MainWindow::drawStatistics()
{
    glEnable(GL_TEXTURE_2D);
    qglColor(QColor(65, 105, 225));
    drawTexture(QRectF{650, 0, 150, 150}, 1);
    drawTexture(QRectF{650, 150, 150, 150}, 1);
    drawTexture(QRectF{650, 300, 150, 150}, 1);
    drawTexture(QRectF{650, 450, 150, 150}, 1);
    glDisable(GL_TEXTURE_2D);
    int y = 100;
    int x = 30;

    for (unsigned int i = Stat::minPrintedLevel; i <= Stat::maxPrintedLevel; ++i)
    {
        QString curStr = LevelsList::GetFNameDir(i).first;
        curStr += "\t";

        int stat = Stat::GetStat(i);

        if (stat == 0) curStr += "Level is not passed";
        else curStr += std::to_string(stat).c_str();
        if (i == Stat::selectedLevel)
        {
            qglColor(QColor(65, 105, 225));
            renderText(x, y, curStr, fontSelected);
            qglColor(Qt::white);
        }
        else
        {
            qglColor(Qt::white);
            renderText(x, y, curStr, font);
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
            gameStatus = SETTINGS;
            ColorPallete::init( 450 , 350 , 200 , 4);
            ColorPallete::placeMarker(FLAGS::manColor);
            break;

        case MENU_STATISTICS:
            gameStatus = STATISTICS;
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

static QString newfilename("custom");
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
        LevelCreator::Write(newfilename + QString::number(100000 + rand() % 900000));
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
void MainWindow::keySettings(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Right:
        ++textureManIndex;
        textureManIndex %= textureManID.size();
        textureID[Texture::MAN] = textureManID[textureManIndex];
        break;

    case Qt::Key_Left:
        textureManIndex += textureManID.size() - 1;
        textureManIndex %= textureManID.size();
        textureID[Texture::MAN] = textureManID[textureManIndex];
        break;

    case Qt::Key_Return:
        FLAGS::manColor = ColorPallete::GetColor();
        saveColors();
        break;
    case Qt::Key_Escape:
        gameStatus = MAIN_MENU;
        break;
    }

    updateGL();
}
void MainWindow::keyStatistics(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Up:
        if (Stat::selectedLevel != 0)
        {
            if (Stat::selectedLevel == Stat::minPrintedLevel)
            {
                --Stat::minPrintedLevel;
                --Stat::maxPrintedLevel;
            }
            --Stat::selectedLevel;
        }
        else
        {
            Stat::selectedLevel = Stat::GetNumber() - 1;
            Stat::maxPrintedLevel = Stat::GetNumber() - 1;
            Stat::minPrintedLevel = Stat::GetNumber() - 7;
        }
        break;

    case Qt::Key_Down:
        if (Stat::selectedLevel != Stat::GetNumber() - 1)
        {
            if (Stat::selectedLevel == Stat::maxPrintedLevel)
            {
             ++Stat::minPrintedLevel;
             ++Stat::maxPrintedLevel;
            }
            ++Stat::selectedLevel;
        }
        else
        {
            Stat::selectedLevel = 0;
            Stat::maxPrintedLevel = 6;
            Stat::minPrintedLevel = 0;
        }
        break;

    case Qt::Key_Escape:
        gameStatus = MAIN_MENU;
        break;
    }

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

    image.load(":/texture/skeleton.png");
    textureManID.push_back(bindTexture(image));

    image.load(":/texture/pig.png");
    textureManID.push_back(bindTexture(image));

    image.load(":/texture/egyptian_walk.png");
    textureManID.push_back(bindTexture(image));

    image.load(":/texture/high_kick.png");
    textureManID.push_back(bindTexture(image));

    textureID[Texture::MAN] = textureManID.front();

    image.load(":/texture/dot.png");
    textureID[Texture::DOT] = bindTexture(image);

    glDisable(GL_TEXTURE_2D);
}

void MainWindow::mousePressEvent(QMouseEvent *mouse){
    mouseHold = true;
    switch (gameStatus)
    {
    case MAIN_MENU:
        break;

    case LEVEL_SELECTION:
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        ColorPallete::Click(mouse->x(), mouse->y());
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
    switch (gameStatus)
    {
    case MAIN_MENU:
        break;

    case LEVEL_SELECTION:
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        ColorPallete::Release();
        break;

    case PLAYING:
        break;

    case LEVEL_CREATOR:
        break;

    case LEVEL_COMPLETED:
        break;
    }
    updateGL();
}
void MainWindow::mouseMoveEvent(QMouseEvent *mouse){
    switch (gameStatus)
    {
    case MAIN_MENU:
        break;

    case LEVEL_SELECTION:
        break;

    case STATISTICS:
        break;

    case SETTINGS:
        if(mouseHold){
            ColorPallete::Hold(mouse->x(), mouse->y());
        }
        break;

    case PLAYING:
        break;

    case LEVEL_CREATOR:
        break;

    case LEVEL_COMPLETED:
        break;
    }
    updateGL();
}

void MainWindow::initColors(){

    //default color pallete

    std::regex R;
    std::smatch m;
    std::string str;
    std::string tempStr;
    std::stack<int> RGB;
    int red = 0;
    int green = 0;
    int blue = 0;
    std::ifstream input("colors.ini");
    if(!input) return;

    while(!input.eof()){
        input >> str;

        R = "[A-Z]{1,}:[0-9]{1,3},[0-9]{1,3},[0-9]{1,3}";

        if(regex_search(str, m, R)){

        R = "[0-9]{1,3}";
        for(int i =0; i < 3; i++){
            regex_search(str, m, R);
            tempStr = m[0];
            std::regex tempR(tempStr);
            str = regex_replace(str, tempR, "" , std::regex_constants::format_first_only);
            RGB.push(stoi(tempStr));
        }

        if(RGB.top() > 255) blue = 255;
        else blue = RGB.top();
        RGB.pop();

        if(RGB.top() > 255) green = 255;
        else green = RGB.top();
        RGB.pop();

        if(RGB.top() > 255) red = 255;
        else red = RGB.top();
        RGB.pop();

        R= "[A-Z]{1,}";

        regex_search(str, m, R);
        tempStr = m[0];

        QColor tempColor(red,green,blue);
        if(tempStr == "WALLCOLOR")          FLAGS::wallColor = tempColor;
        if(tempStr == "OUTSIDECOLOR")       FLAGS::outsideColor = tempColor;
        if(tempStr == "EMPTYCOLOR")         FLAGS::emptyColor = tempColor;
        if(tempStr == "MANCOLOR")           FLAGS::manColor = tempColor;
        if(tempStr == "BOXCOLOR")           FLAGS::boxColor  = tempColor;
        if(tempStr == "POINTCOLOR")         FLAGS::pointColor = tempColor;
        if(tempStr == "CIRCLEBOXCOLOR")     FLAGS::circleBoxColor = tempColor;
        if(tempStr == "SPAWNCOLOR")         FLAGS::spawnColor = tempColor;
        if(tempStr == "ERASERCOLOR")        FLAGS::eraserColor  = tempColor;
        if(tempStr == "FRAMECOLOR")         FLAGS::frameColor = tempColor;
        }
    }
}

void MainWindow::saveColors(){
    QColor tempColor;
    std::ofstream output("colors.ini");
    output << "COLORS:\n";

    tempColor = FLAGS::wallColor;
    output << "WALLCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::outsideColor;
    output << "OUTSIDECOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::emptyColor;
    output << "EMPTYCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::manColor;
    output << "MANCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::boxColor;
    output << "BOXCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::pointColor;
    output << "POINTCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::circleBoxColor;
    output << "CIRCLEBOXCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::spawnColor;
    output << "SPAWNCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::eraserColor;
    output << "ERASERCOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue()<<"\n";

    tempColor = FLAGS::frameColor;
    output << "FRAMECOLOR:";
    output <<tempColor.red()<<","<<tempColor.green()<<","<<tempColor.blue();
}
