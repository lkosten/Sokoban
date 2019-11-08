#include "bintoint.h"
#include <cmath>

unsigned int BinToInt(QByteArray& arr, unsigned int t){
    unsigned int ret = 0;
    for (unsigned int i =0;i<4;i++){
        ret += (unsigned int)(char)arr[t+i] * pow(256,i);
    }
    return ret;
}
