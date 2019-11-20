#include "ColorPallete.h"

qreal ColorPallete::R = 255;
qreal ColorPallete::G = 0;
qreal ColorPallete::B = 0;

int ColorPallete::sR = 0;
int ColorPallete::sG = 0;
int ColorPallete::sB = 0;

qreal ColorPallete::ColumnX = 0;
qreal ColorPallete::ColumnY = 0;

qreal ColorPallete::ColumnH = 255;
qreal ColorPallete::ColumnW = 10;

qreal ColorPallete::PalleteX = 0;
qreal ColorPallete::PalleteY = 0;
qreal ColorPallete::PalleteH = 0;
qreal ColorPallete::PalleteAcc = 1;

qreal ColorPallete::SelectX = 0;
qreal ColorPallete::SelectY = 0;

qreal ColorPallete::FrameY = 0;

bool ColorPallete::changing = false;
bool ColorPallete::selecting = false;

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

    //draw frame
    window.qglColor(QColor(255,255,255));
    window.drawTexture(QRectF{X-3, Y-3, blockSize*mult*255 + 6, blockSize*mult*255 + 6},
                       window.textureID[Texture::FRAME]);


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

            if(X + (j+accuracy)*mult > ColorPallete::SelectX && ColorPallete::SelectX >= X + j*mult){
                if(Y + (i+accuracy)*mult > ColorPallete::SelectY && ColorPallete::SelectY >= Y + i*mult){
                    ColorPallete::sR = static_cast<int>(tR + j*(mainColor - tR)/255);
                    ColorPallete::sG = static_cast<int>(tG + j*(mainColor - tG)/255);
                    ColorPallete::sB = static_cast<int>(tB + j*(mainColor - tB)/255);
                }
            }
        }
    }
    if(X + H < ColorPallete::SelectX){
        ColorPallete::SelectX = X+H;
    }
    if(X > ColorPallete::SelectX){
        ColorPallete::SelectX = X;
    }
    if(Y + H < ColorPallete::SelectY){
        ColorPallete::SelectY = Y+H;
    }
    if(Y > ColorPallete::SelectY){
        ColorPallete::SelectY = Y;
    }
    window.qglColor(QColor(255,255,255));
    window.drawTexture(QRectF{ColorPallete::SelectX - 2.5*mult, ColorPallete::SelectY -  2.5*mult, blockSize*5*mult, blockSize*5*mult},
                       window.textureID[Texture::DOT]);
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
void ColorPallete::Hold(qreal X, qreal Y){
    if(changing){
        ColorPallete::FrameY = Y;
    }
    if(selecting){
        ColorPallete::SelectX = X;
        ColorPallete::SelectY = Y;
    }
}
void ColorPallete::Click(qreal X, qreal Y){
    if(X <= ColumnX + ColumnW && X >= ColumnX){
        if(Y <= ColumnY + ColumnH && Y >= ColumnY){
            changing = true;
            ColorPallete::FrameY = Y;
        }
    }
    if(X <= PalleteH + PalleteX && X >= PalleteX){
        if(Y <= PalleteH + PalleteY && Y >= PalleteY){
            qDebug() <<"matrix click";
            selecting = true;
            ColorPallete::SelectX = X;
            ColorPallete::SelectY = Y;
        }
    }
}
void ColorPallete::Release(){
    changing = false;
    selecting = false;
}

QColor ColorPallete::GetColor(){
    QColor temp(sR,sG,sB);
    return temp;
}
void ColorPallete::placeMarker(QColor color){

    int R,G,B;

    R = color.red();
    G = color.green();
    B = color.blue();

    //FOR COLUMN FRAME
    int stage = 0;
    int itR = 255;
    int itG = 0;
    int itB = 0;
    int change = 6;
    int findR = 0 , findG = 0 , findB = 0;

    //SELECT 2 MAIN COMPONENTS
    if(R <= G && R <= B){
       findR = 0;
       if(G <= B){
           findB = 255;
           findG = G*255/B;
       }
       else{
           findG = 255;
           findB = B*255/G;
       }
    }
    if(G <= R && G <= B){
       findG = 0;
       if(R <= B){
           findB = 255;
           findR = R*255/B;
       }
       else{
           findR = 255;
           findB = B*255/R;
       }
    }
    if(B <= R && B <= G){
       findB = 0;
       if(R <= G){
           findG = 255;
           findR = R*255/G;
       }
       else{
           findR = 255;
           findG = G*255/R;
       }
    }

    //SEEK THEESE COMPONENTS
    for(qreal i = 0; true ; i++){

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

       //PLACE FRAME THERE IF FOUND
        if(itR <= findR && findR < itR + change){
            if(itG <= findG && findG < itG + change){
                if(itB <= findB && findB < itB + change){
                    ColorPallete::FrameY = ColorPallete::PalleteY + i*ColorPallete::PalleteH/255;
                    break;
                }
            }
        }
    }

    //SEEK DOT KNOWING 2 MAIN COMPONENTS

    qreal tR,tG,tB;
    qreal mainColor;

    for(qreal i = 0; i < 256; i+= 5){

        //get temporary variables
        tR=findR - findR/255 * i;
        tG=findG - findG/255 * i;
        tB=findB - findB/255 * i;

        mainColor = std::max(tR, std::max(tG, tB));//number that was 255 is main , other temporary variables are heading to it current temporary value

        //PLACE DOT THERE IF FOUND
        for(qreal j = 0; j < 256; j += 5){
            if(abs(tR + j*(mainColor - tR)/255 - R) <= 3){
                if(abs(tG + j*(mainColor - tG)/255 - G) <= 3){
                    if(abs(tB + j*(mainColor - tB)/255 - B) <= 3){
                        ColorPallete::SelectX = ColorPallete::PalleteX + j*ColorPallete::PalleteH/255;
                        ColorPallete::SelectY = ColorPallete::PalleteY + i*ColorPallete::PalleteH/255;
                    }
                }
            }
        }
    }
}
