#include "Object.h"
#include "../Scene/Scene.h"

Object::Object(Scene* _currentScene) : Object(_currentScene, {0,0},{0,0}){
}

Object::Object(Scene* _currentScene, sf::Vector2f _size) : Object(_currentScene, _size, {0,0}) {
}

Object::Object(Scene* _currentScene, sf::Vector2f _size, sf::Vector2f _position) : currentScene(_currentScene), size(_size), position(_position) {
}


Object::~Object() {
    for (auto& component : myComponents) {
        delete component;
        component = nullptr;
    }
    myComponents.clear();
}


std::string& Object::getName() {
    return name;
}

sf::Vector2f& Object::getPosition() {
    return position;
}

sf::Vector2f& Object::getSize() {
    return size;
}

Scene* Object::getCurrentScene() {
    return currentScene;
}


void Object::setName(std::string _name) {
    name = _name;
}

void Object::setPosition(sf::Vector2f _position) {
    position = _position;
}

void Object::setSize(sf::Vector2f _size) {
    size = _size;
}


void Object::addComponent(Component* component) {
    myComponents.push_back(component);
}

void Object::removeComponent(Component* component) {
    auto it = std::find(myComponents.begin(), myComponents.end(), component);
    
    if (it != myComponents.end()) {
        delete *it;
        myComponents.erase(it);  
    }
}


void Object::update(float& deltaTime) {
    if (!myComponents.empty()) {
        for (auto& component : myComponents) {
            component->update(deltaTime);
        }
    }
}

void Object::render() {
    if (!myComponents.empty()) {
        for (auto& component : myComponents) {
            component->render();
        }
    }
}
