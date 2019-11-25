#include "bintoint.h"
#include <cmath>

unsigned int BinToInt(QDataStream &Input){
    quint8 i;
    unsigned int ret = 0;
    unsigned int mult = 1;
    for(int j =0;j<4;j++){
        Input >> i;
        ret += i * mult;
        mult *= 256;
    }
    return ret;
}
