#include "Reader.h"

Reader::Reader(std::string _path) : path(_path){
}

std::string& Reader::getPath() {
    return path;
}
