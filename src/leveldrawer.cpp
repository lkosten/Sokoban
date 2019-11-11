#include "leveldrawer.h"

QColor LevelDrawer::wallColor      = Qt::darkMagenta;
QColor LevelDrawer::outsideColor   = Qt::white;
QColor LevelDrawer::emptyColor     = Qt::white;
QColor LevelDrawer::manColor       = Qt::white;
QColor LevelDrawer::boxColor       = Qt::yellow;
QColor LevelDrawer::pointColor     = Qt::red;
QColor LevelDrawer::circleBoxColor = Qt::white;

void LevelDrawer::fullRender(MainWindow &window)
{
    qreal curX = protectedAreaX / 2;
    qreal curY = protectedAreaY / 2;

    qreal blockSize = std::min((window.windowWidth - protectedAreaX) / LevelHandler::Field.front().size(),
                                (window.windowHeight - protectedAreaY) / LevelHandler::Field.size());

    glEnable(GL_TEXTURE_2D);
    for (const auto &curRow : LevelHandler::Field)
    {
        curX = protectedAreaX / 2;
        for (const auto &curElement : curRow)
        {
            switch (curElement)
            {
            case LevelHandler::BOX:
                window.qglColor(boxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;

            case LevelHandler::WALL:
                window.qglColor(wallColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::WALL]);
                break;

            case LevelHandler::EMPTY:
                window.qglColor(emptyColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::EMPTY]);
                break;

            case LevelHandler::POINT:
                window.qglColor(pointColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                break;

            case LevelHandler::OUTSIDE:
                window.qglColor(outsideColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::OUTSIDE]);
                break;

            case LevelHandler::BOX_ON_POINT:
                window.qglColor(circleBoxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                window.qglColor(boxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;
            }

            curX += blockSize;
        }

        curY += blockSize;
    }

    curX = protectedAreaX / 2 + LevelHandler::PosX * blockSize;
        curY = protectedAreaY / 2 + LevelHandler::PosY * blockSize;

        window.qglColor(manColor);
        window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                           window.textureID[Texture::MAN]);

    glDisable(GL_TEXTURE_2D);

}
