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
QColor CreatorDrawer::frameColor     = Qt::white;

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

            window.qglColor(frameColor);
            window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                               window.textureID[Texture::FRAME]);

            curX += blockSize;
        }
        curY += blockSize;
    }


    curX = FieldX + CreatorMap::PosX * blockSize;
    curY = FieldY + CreatorMap::PosY * blockSize;

    window.qglColor(manColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::SPAWNPOINT]);

    curY = ToolsY;
    curX = ToolsX;
    blockSize = FieldHeight / 5;

    window.qglColor(frameColor);
    window.drawTexture(QRectF{curX, curY + blockSize * CreatorBrush::GetToolNum(), blockSize, blockSize},
                       window.textureID[Texture::FRAME]);

    window.qglColor(eraserColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::ERASER]);

    curY +=blockSize;

    window.qglColor(wallColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::WALL]);

    curY +=blockSize;

    window.qglColor(boxColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::BOX]);

    curY +=blockSize;

    window.qglColor(pointColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::CIRCLE]);

    curY +=blockSize;

    window.qglColor(spawnColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::SPAWNPOINT]);

    curY = ToolsY;

    window.qglColor(frameColor);
    window.drawTexture(QRectF{curX, curY + blockSize * CreatorBrush::GetToolNum(), blockSize, blockSize},
                       window.textureID[Texture::FRAME]);

    glDisable(GL_TEXTURE_2D);

}
