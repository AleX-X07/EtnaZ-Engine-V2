#pragma once
#include <vector>

#include "Component/Component.h"

class Object {
private:
    std::string name;
    
    sf::Vector2f position;
    sf::Vector2f size;
    
    std::vector<Component*> myComponents;
    
public:
    Object();
    Object(sf::Vector2f _size);
    Object(sf::Vector2f _size, sf::Vector2f _position);
    
    virtual ~Object();
    
    std::string& getName();
    sf::Vector2f& getPosition();
    sf::Vector2f& getSize();
    
    void setName(std::string _name);
    void setPosition(sf::Vector2f _position);
    void setSize(sf::Vector2f _size);
    
    void addComponent(Component* component);
    void removeComponent(Component* component);
    
    virtual void update(float& deltaTime);
    virtual void render();
    
    // Template 
    template <typename T> T* getComponent() {
        for (auto& comp : myComponents) {
            auto* c = dynamic_cast<T*>(comp);
            if (c != nullptr) {
                return c;
            }
        }
        return nullptr;
    }
    
    template <typename T> bool hasComponent() {
        for (auto& comp : myComponents) {
            auto* c = dynamic_cast<T*>(comp);
            if (c && c != nullptr) {
                return true;
            }
        }
        return false;
    }
    
};
