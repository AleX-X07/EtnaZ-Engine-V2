#pragma once

#include "../Object/Object.h"

class Layer {
private:   
    std::vector<std::vector<Object*>> layers;
    int nbrLayers;
    
public:
    Layer();
    ~Layer() = default;
    
    void setNbrLayer(int nbrLayers);
    void addInLayer(Object* myObject, int layer);
    
    void render();
};
