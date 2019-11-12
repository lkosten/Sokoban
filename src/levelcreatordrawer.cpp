#include "levelcreatordrawer.h"

QColor CreatorDrawer::wallColor      = Qt::darkMagenta;
QColor CreatorDrawer::outsideColor   = Qt::white;
QColor CreatorDrawer::emptyColor     = Qt::white;
QColor CreatorDrawer::manColor       = Qt::white;
QColor CreatorDrawer::boxColor       = Qt::yellow;
QColor CreatorDrawer::pointColor     = Qt::red;
QColor CreatorDrawer::circleBoxColor = Qt::green;
QColor CreatorDrawer::spawnColor     = Qt::white;
QColor CreatorDrawer::eraserColor    = Qt::blue;

void CreatorDrawer::fullRender(MainWindow &window)
{

    qreal blockSize = std::min(FieldWidth/CreatorMap::SizeX , FieldHeight/CreatorMap::SizeY);
    qreal curX = FieldX;
    qreal curY = FieldY;

    glEnable(GL_TEXTURE_2D);

    for(unsigned int i =0;i < CreatorMap::SizeY; i++){
        curX = FieldX;
        for(unsigned int j =0;j < CreatorMap::SizeX; j++){
            switch (CreatorMap::Field[j][i])
            {
            case CreatorMap::BOX:
                window.qglColor(boxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;

            case CreatorMap::WALL:
                window.qglColor(wallColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::WALL]);
                break;

            case CreatorMap::EMPTY:
                window.qglColor(emptyColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::EMPTY]);
                break;

            case CreatorMap::POINT:
                window.qglColor(pointColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                break;

            case CreatorMap::OUTSIDE:
                window.qglColor(outsideColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::OUTSIDE]);
                break;

            case CreatorMap::BOX_ON_POINT:
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


    curX = FieldX + CreatorMap::PosX * blockSize;
        curY = FieldY + CreatorMap::PosY * blockSize;

        window.qglColor(manColor);
        window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                           window.textureID[Texture::SPAWNPOINT]);

    glDisable(GL_TEXTURE_2D);

}
