#pragma once
#include <iostream>

class Reader {
private:
    std::string path;

public:
    Reader(std::string _path);
    virtual ~Reader() = default;
    
    std::string& getPath();
};
