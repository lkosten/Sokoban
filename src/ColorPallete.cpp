#include "ColorPallete.h"

std::vector<std::vector<RGB>> ColorPallete::matrix = std::vector<std::vector<RGB>>();

void ColorPallete::draw(MainWindow &window){
    qreal blockSize = 1;
    qreal curX = 100;
    qreal curY = 100;
    qreal R,G,B;
    R = 255;
    G = 0;
    B = 170;
    qreal tR,tG,tB;
    qreal mainColor;
    for(qreal i = 0; i < 256; i++){
        tR=R - R/255 * i;
        tG=G - G/255 * i;
        tB=B - B/255 * i;
        mainColor = std::max(tR, std::max(tG, tB));
        for(qreal j = 0; j < 256; j++){
            window.qglColor(QColor(tR + j*(mainColor - tR)/255, tG + j*(mainColor - tG)/255, tB + j*(mainColor - tB)/255));
            window.drawTexture(QRectF{curX + j, curY + i, blockSize, blockSize},
                               window.textureID[Texture::DOT]);
        }
    }
    int itR = 255;
    int itG = 0;
    int itB = 0;
    int stage = 0;
    for(qreal i = 0; i < 43*6; i++){
        switch (stage){
            case 0:{
                itB += 6;
                if(itB == 258) {
                    itB -= 3;
                    itR -= 3;
                    stage = 1;
                }
                break;
            }
            case 1:{
                itR -= 6;
                if(itR == 0) {
                    stage = 2;
                }
                break;
            }
            case 2:{
                itG += 6;
                if(itG == 258) {
                    itG -= 3;
                    itB -= 3;
                    stage = 3;
                }
                break;
            }
            case 3:{
                itB -= 6;
                if(itB == 0) {
                    stage = 4;
                }
                break;
            }
            case 4:{
                itR += 6;
                if(itR == 258) {
                    itR -= 3;
                    itG -=3;
                    stage = 5;
                }
                break;
            }
                case 5:{
                itG -= 6;
                if(itG == 0) {
                    stage = 6;
                }
                break;
            }
        }

        window.qglColor(QColor(itR, itG, itB));
        window.drawTexture(QRectF{curX + 300, curY + i, blockSize*10, blockSize},
                           window.textureID[Texture::DOT]);

        if(stage == 6) break;
    }
}

