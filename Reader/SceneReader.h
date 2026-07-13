#pragma once
#include <unordered_map>
#include <fstream>

#include "Reader.h"

class Scene;

class SceneReader : public Reader {
private:
    std::unordered_map<int,Scene*> myScene;
    
public:
    SceneReader(std::string _path);
    virtual ~SceneReader() override;
    
    std::unordered_map<int,Scene*>& getScene();
};
