#include "levelcreatordrawer.h"

void CreatorDrawer::fullRender(MainWindow &window)
{

    qreal blockSize = std::min(FieldWidth/CreatorMap::SizeX , FieldHeight/CreatorMap::SizeY);
    qreal curX = FieldX;
    qreal curY = FieldY;

    for(unsigned int i =0;i < CreatorMap::SizeY; i++){
        curX = FieldX;
        for(unsigned int j =0;j < CreatorMap::SizeX; j++){

            switch (CreatorMap::Field[j][i])
            {
            case FLAGS::BOX:
                window.qglColor(FLAGS::boxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;

            case FLAGS::WALL:
                window.qglColor(FLAGS::wallColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::WALL]);
                break;

            case FLAGS::EMPTY:
                window.qglColor(FLAGS::emptyColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::EMPTY]);
                break;

            case FLAGS::POINT:
                window.qglColor(FLAGS::pointColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                break;

            case FLAGS::OUTSIDE:
                window.qglColor(FLAGS::outsideColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::OUTSIDE]);
                break;

            case FLAGS::BOX_ON_POINT:
                window.qglColor(FLAGS::circleBoxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::CIRCLE]);
                window.qglColor(FLAGS::boxColor);
                window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                                   window.textureID[Texture::BOX]);
                break;
            }

            window.qglColor(FLAGS::frameColor);
            window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                               window.textureID[Texture::FRAME]);

            curX += blockSize;
        }
        curY += blockSize;
    }


    curX = FieldX + CreatorMap::PosX * blockSize;
    curY = FieldY + CreatorMap::PosY * blockSize;

    window.qglColor(FLAGS::manColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::SPAWNPOINT]);

    curY = ToolsY;
    curX = ToolsX;
    blockSize = FieldHeight / 5;

    window.qglColor(FLAGS::frameColor);
    window.drawTexture(QRectF{curX, curY + blockSize * CreatorBrush::GetToolNum(), blockSize, blockSize},
                       window.textureID[Texture::FRAME]);

    window.qglColor(FLAGS::eraserColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::ERASER]);

    curY +=blockSize;

    window.qglColor(FLAGS::wallColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::WALL]);

    curY +=blockSize;

    window.qglColor(FLAGS::boxColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::BOX]);

    curY +=blockSize;

    window.qglColor(FLAGS::pointColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::CIRCLE]);

    curY +=blockSize;

    window.qglColor(FLAGS::spawnColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::SPAWNPOINT]);

    curY = ToolsY;

    window.qglColor(FLAGS::frameColor);
    window.drawTexture(QRectF{curX, curY + blockSize * CreatorBrush::GetToolNum(), blockSize, blockSize},
                       window.textureID[Texture::FRAME]);


    QFont currentFont;
    currentFont.setPixelSize(50);
    size_t PixelSize = static_cast<size_t>(currentFont.pixelSize());
    window.qglColor(QColor(255, 255, 255));

    int counter = 0;
    unsigned int tempSize = CreatorMap::SizeX;
    while(tempSize){
        counter++;
        tempSize/=10;
    }
    if(counter == 2)
    window.renderText(XresizeX - 25, static_cast<int>(XresizeY + PixelSize) - 5, QString::number(CreatorMap::SizeX), currentFont);
    else
    window.renderText(XresizeX - 5, static_cast<int>(XresizeY + PixelSize) - 5, QString::number(CreatorMap::SizeX), currentFont);

    window.qglColor(QColor(200, 55, 90));
    window.drawTexture(QRectF{XresizeX - 75, XresizeY, 50, 50},
                       window.textureID[Texture::MINUS]);

    window.qglColor(QColor(200, 55, 90));
    window.drawTexture(QRectF{XresizeX + 25, XresizeY, 50, 50},
                       window.textureID[Texture::PLUS]);



    window.qglColor(QColor(255, 255, 255));

    counter = 0;
    tempSize = CreatorMap::SizeY;
    while(tempSize){
        counter++;
        tempSize/=10;
    }
    if(counter == 2)
    window.renderText(YresizeX, static_cast<int>(YresizeY + PixelSize/2) - 5, QString::number(CreatorMap::SizeY), currentFont);
    else
    window.renderText(YresizeX + 15, static_cast<int>(YresizeY + PixelSize/2) - 5, QString::number(CreatorMap::SizeY), currentFont);

    window.qglColor(QColor(200, 55, 90));
    window.drawTexture(QRectF{YresizeX, YresizeY + 25, 50, 50},
                       window.textureID[Texture::MINUS]);

    window.qglColor(QColor(200, 55, 90));
    window.drawTexture(QRectF{YresizeX, YresizeY - 75, 50, 50},
                       window.textureID[Texture::PLUS]);

}
