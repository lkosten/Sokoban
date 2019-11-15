#include "leveldrawer.h"

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
            case FLAGS::BOX:
                window.qglColor(FLAGS::boxColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;

            case FLAGS::WALL:
                window.qglColor(FLAGS::wallColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::WALL]);
                break;

            case FLAGS::EMPTY:
                window.qglColor(FLAGS::emptyColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::EMPTY]);
                break;

            case FLAGS::POINT:
                window.qglColor(FLAGS::pointColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                break;

            case FLAGS::OUTSIDE:
                window.qglColor(FLAGS::outsideColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::OUTSIDE]);
                break;

            case FLAGS::BOX_ON_POINT:
                window.qglColor(FLAGS::circleBoxColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                window.qglColor(FLAGS::boxColor);
                window.drawTexture(QRectF{curY, curX, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;
            }

            curX += blockSize;
        }

        curY += blockSize;
    }

    curX = protectedAreaY / 2 + LevelHandler::PosX * blockSize;
        curY = protectedAreaX / 2 + LevelHandler::PosY * blockSize;

        window.qglColor(FLAGS::manColor);
        window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                           window.textureID[Texture::MAN]);

    glDisable(GL_TEXTURE_2D);

}
