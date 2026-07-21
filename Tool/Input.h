#pragma once
#include "SFML/Graphics.hpp"

using InputMap = std::unordered_map<std::string, sf::Keyboard::Key>;

class Input {
private:
    static Input* myInstance;

    InputMap inputMap;
    
    bool keyPressed;
    sf::Keyboard::Key key;

    bool mousePressed;
    sf::Mouse::Button mouse;
    sf::Vector2i mousePos;
    
    float factWheelScrolled;
    
    Input() = default;
    
public:
    ~Input();
    
    static Input* getInstance();
    
    void setEvent(sf::Event event);
    void reset();
    
    InputMap& getMap();
    sf::Keyboard::Key getKey(const std::string& key);
    
    bool isKeyPressed(sf::Keyboard::Key key);
    bool isMousePressed(sf::Mouse::Button button);
    
    float getWheelScrolled();
    
    void deleteSingleton();
};