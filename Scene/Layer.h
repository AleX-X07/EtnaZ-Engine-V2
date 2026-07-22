#pragma once

#include "../Object/Object.h"

class Layer {
private:   
    std::vector<std::vector<Object*>> layers;
    int nbrLayers;
    
public:
    Layer();
    ~Layer();
    
    std::vector<std::vector<Object*>>& getVecLayers();
    
    void setNbrLayer(int nbrLayers);
    void addInLayer(Object* myObject, int layer);
    
    int getCurrentLayer(Object* myObject);
    
    void render();
};
