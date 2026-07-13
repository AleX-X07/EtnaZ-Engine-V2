#include "SceneReader.h"
#include "../Scene/Scene.h"

SceneReader::SceneReader(std::string _path) : Reader(_path){
    std::ifstream scene(_path);
    
}

SceneReader::~SceneReader() {
    for (auto& [k,v] : myScene) {
        delete v;
        v= nullptr;
    }
}

std::unordered_map<int, Scene*>& SceneReader::getScene() {
    return myScene;
}
