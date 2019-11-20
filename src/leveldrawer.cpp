#include "leveldrawer.h"

void LevelDrawer::fullRender(MainWindow &window)
{
    qreal blockSize = std::min((window.windowWidth - protectedAreaX) /
                               (LevelHandler::Field.size() - 2),
                                (window.windowHeight - protectedAreaY) /
                               (LevelHandler::Field.front().size() - 2));

    size_t areaX = window.windowWidth - static_cast<size_t>(blockSize) * (LevelHandler::Field.size() - 2);
    areaX /= 2;

    size_t areaY = window.windowHeight - static_cast<size_t>(blockSize) * (LevelHandler::Field.front().size() - 2);
    areaY /= 2;

    qreal curX = areaX;
    qreal curY = areaY;

    glEnable(GL_TEXTURE_2D);
    for (size_t i = 1; i < LevelHandler::Field.size() - 1; ++i)
    {
        curY = areaY;
        for (size_t j = 1; j < LevelHandler::Field[i].size() - 1; ++j)
        {
            char curElement = LevelHandler::Field[i][j];
            switch (curElement)
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

            curY += blockSize;
        }

        curX += blockSize;
    }

    curX = areaX + (LevelHandler::PosX - 1) * blockSize;
    curY = areaY + (LevelHandler::PosY - 1) * blockSize;

    window.qglColor(FLAGS::manColor);
    window.drawTexture(QRectF{curX, curY, blockSize, blockSize},
                       window.textureID[Texture::MAN]);

    renderStats(window);

    if (LevelLogic::CheckNum())
    {
        window.gameStatus = LEVEL_COMPLETED;

        window.qglColor(FLAGS::manColor);
        window.renderText(30, static_cast<int>(window.windowHeight - protectedAreaY / 2 + 40),
                          "Level completed!", window.fontSmall);
        window.renderText(30, static_cast<int>(window.windowHeight - protectedAreaY / 2 + 90),
                          "Press space to continue...", window.fontSmall);
    }
    glDisable(GL_TEXTURE_2D);

}

void LevelDrawer::renderStats(MainWindow &window)
{
    std::string moves = "Moves: " + std::to_string(Stat::getMoves());
    std::string pushes = "Pushes: " + std::to_string(Stat::getPushes());

    window.renderText(30, 40, moves.c_str(), window.fontSmall);
    window.renderText(30, 90, pushes.c_str(), window.fontSmall);
}
