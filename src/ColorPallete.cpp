#include "ColorPallete.h"

qreal ColorPallete::R = 255;
qreal ColorPallete::G = 0;
qreal ColorPallete::B = 0;

qreal ColorPallete::ColumnX = 0;
qreal ColorPallete::ColumnY = 0;

qreal ColorPallete::ColumnH = 255;
qreal ColorPallete::ColumnW = 10;

qreal ColorPallete::PalleteX = 0;
qreal ColorPallete::PalleteY = 0;
qreal ColorPallete::PalleteH = 0;
qreal ColorPallete::PalleteAcc = 1;

qreal ColorPallete::FrameY = 0;

bool ColorPallete::changing = false;

std::vector<std::vector<RGB>> ColorPallete::matrix = std::vector<std::vector<RGB>>();

void ColorPallete::init(qreal X, qreal Y, qreal H, qreal accuracy){
    ColorPallete::PalleteX = X;
    ColorPallete::PalleteY = Y;
    ColorPallete::PalleteH = H;
    ColorPallete::PalleteAcc = accuracy;
}

void ColorPallete::draw(MainWindow &window){
    drawColumn(window);
    drawMatrix(window);
}

void ColorPallete::drawMatrix(MainWindow &window){
    qreal X =  ColorPallete::PalleteX, Y =  ColorPallete::PalleteY, H = ColorPallete::PalleteH, accuracy =  ColorPallete::PalleteAcc;
    qreal mult = H/255;
    qreal blockSize = 1;
    qreal tR,tG,tB;
    qreal mainColor;
    //draw colourfull square
    for(qreal i = 0; i < 256; i+= accuracy){

        //get temporary variables
        tR=ColorPallete::R - ColorPallete::R/255 * i;
        tG=ColorPallete::G - ColorPallete::G/255 * i;
        tB=ColorPallete::B - ColorPallete::B/255 * i;

        mainColor = std::max(tR, std::max(tG, tB));//number that was 255 is main , other temporary variables are heading to it current temporary value

        //"heading" process
        for(qreal j = 0; j < 256; j += accuracy){
            window.qglColor(QColor(static_cast<int>(tR + j*(mainColor - tR)/255),
                                   static_cast<int>(tG + j*(mainColor - tG)/255),
                                   static_cast<int>(tB + j*(mainColor - tB)/255)));
            window.drawTexture(QRectF{X + j*mult, Y + i*mult, blockSize*mult*accuracy, blockSize*mult*accuracy},
                               window.textureID[Texture::DOT]);
        }
    }
}
void ColorPallete::drawColumn(MainWindow &window){
    qreal X =  ColorPallete::PalleteX, Y =  ColorPallete::PalleteY, H = ColorPallete::PalleteH, accuracy =  ColorPallete::PalleteAcc;
    qreal mult = H/255;//number that we need to multiply on 255 to get H size
    qreal blockSize = 1;
    ColorPallete::ColumnX = X + 300*mult;
    ColorPallete::ColumnY = Y;
    ColorPallete::ColumnH = H;
    ColorPallete::ColumnW = 10*mult;
    int itR = 255;
    int itG = 0;
    int itB = 0;
    int stage = 0;
    int change = 6;
    //draw column
    for(qreal i = 0; true ; i++){
        //save RGB if we processing place of Frame
        if( Y + (i + accuracy)*mult > ColorPallete::FrameY && Y + i*mult <= ColorPallete::FrameY){
            ColorPallete::R = itR;
            ColorPallete::G = itG;
            ColorPallete::B = itB;
        }

        switch (stage){
            case 0:{//Blue is rising to 255
                itB += change;
                if(itB == 258) {
                    itB -= change/2;
                    itR -= change/2;
                    stage = 1;
                }
                break;
            }
            case 1:{//Red is decreasing to 0
                itR -= change;
                if(itR == 0) {
                    stage = 2;
                }
                break;
            }
            case 2:{//Green is rising to 255
                itG += change;
                if(itG == 258) {
                    itG -= change/2;
                    itB -= change/2;
                    stage = 3;
                }
                break;
            }
            case 3:{//Blue is decreasing to 0
                itB -= change;
                if(itB == 0) {
                    stage = 4;
                }
                break;
            }
            case 4:{//Red is rising to 255
                itR += change;
                if(itR == 258) {
                    itR -= change/2;
                    itG -= change/2;
                    stage = 5;
                }
                break;
            }
                case 5:{//Green is decreasing to 0
                itG -= change;
                if(itG == 0) {
                    stage = 6;
                }
                break;
            }
        }

        window.qglColor(QColor(itR, itG, itB));
        window.drawTexture(QRectF{X + 300*mult, Y + i*mult, blockSize*10*mult, blockSize*mult},
                           window.textureID[Texture::DOT]);

        if(stage == 6) break;
    }

    //draw selection frame
    if(Y <= ColorPallete::FrameY && ColorPallete::FrameY <= Y + H){

        window.qglColor(QColor(255,255,255));
        window.drawTexture(QRectF{X + 300*mult - 5 , ColorPallete::FrameY, blockSize*10*mult + 10, blockSize*5*mult},
                           window.textureID[Texture::DOT]);
    }
}
void ColorPallete::Hold(qreal Y){
    if(changing){
        ColorPallete::FrameY = Y;
    }
}
void ColorPallete::Click(qreal X, qreal Y){
    if(X <= ColumnX + ColumnW && X >= ColumnX){
        if(Y <= ColumnY + ColumnH && Y >= ColumnY){
            changing = true;
            ColorPallete::FrameY = Y;
        }
    }
}
void ColorPallete::Release(){
    changing = false;
}

