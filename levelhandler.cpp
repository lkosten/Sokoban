#include "levelhandler.h"
#include "logs.h"

LevelHandler::LevelHandler(){}

LevelHandler::LevelHandler(const char* file_name){
    FILE *input = std::fopen(file_name, "rb");
    if (input == NULL){
        std::string out = "no such file :";
        out+= file_name;
        printlog(out);
    }
}
