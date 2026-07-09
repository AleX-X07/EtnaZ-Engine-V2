#include "Input.h"

#include "SFML/Window/Event.hpp"

Input* Input::myInstance = nullptr;

Input::~Input() {
}


InputMap& Input::getMap() {
    return inputMap;
}

sf::Keyboard::Key Input::getKey(const std::string& key) {
    auto it = inputMap.find(key);
    if (it != inputMap.end()) {
        return it->second;
    }
    return sf::Keyboard::Key::Unknown;
}

Input* Input::getInput() {
    if (myInstance == nullptr) {
        myInstance = new Input();
    }
    return myInstance;
}


void Input::setEvent(sf::Event event) {
    if (auto* k = event.getIf<sf::Event::KeyPressed>()) {
        keyPressed = true;
        key = k->code;
    }
    else if (auto* m = event.getIf<sf::Event::MouseButtonPressed>()) {
        mousePressed = true;
        mouse = m->button;
        mousePos = m->position;
    }
}


void Input::reset() {
    keyPressed = false;
    mousePressed = false;
}


bool Input::isKeyPressed(sf::Keyboard::Key _key) {
    return keyPressed && key == _key;
}

bool Input::isMousePressed(sf::Mouse::Button _button) {
    return mousePressed && mouse == _button;
}

void Input::deleteSingleton() {
    delete myInstance;
    myInstance = nullptr;
}
