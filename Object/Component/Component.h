#pragma once
#include "SFML/Graphics.hpp"

class Object;

class Component {
protected:
    Object* owner;
    
public:
    Component(Object* _owner);
    virtual ~Component() = default;
    
    void setOwner(Object* _owner);
    
    virtual void update(float& deltaTime);
    virtual void render();
};
