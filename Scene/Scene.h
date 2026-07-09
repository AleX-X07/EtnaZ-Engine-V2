#pragma once

#include "Layer.h"
#include "../Object/Object.h"

class Scene {
private:
    std::vector<Object*> myObjects;
    Layer* myLayer;
    
    int idScene;
    
public:
    Scene();
    Scene(int _idScene);
    virtual ~Scene();
    
    std::vector<Object*>& getMyObjects();
    Layer* getLayer();
    int& getIdScene();
    
    void addObjectInScene(Object* obj);
    void addObjectInScene(Object* obj, int layer);
    
    virtual void update(float& deltaTime);
    virtual void render();
};
