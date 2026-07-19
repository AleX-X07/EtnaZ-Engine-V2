#include "MouseComponent.h"
#include "../../../Main/GameEngine.h"

MouseComponent::MouseComponent(Object* _owner) : Component(_owner), selected(false) {
}

void MouseComponent::update(float& deltaTime) {
    
}

sf::Vector2i MouseComponent::getMousePosition() {
    return sf::Mouse::getPosition(*GameEngine::getWindow());
}

bool MouseComponent::isClicked() {
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*GameEngine::getWindow());
    sf::Vector2f mousePos = GameEngine::getWindow()->mapPixelToCoords(mousePixel, GameEngine::getWindow()->getDefaultView()); 
    
    sf::FloatRect bounds(
        {owner->getPosition().x,
        owner->getPosition().y},
        {owner->getSize().x,
        owner->getSize().y}
    );
    
    if (Input::getInstance()->isMousePressed(sf::Mouse::Button::Left) && bounds.contains(sf::Vector2f(mousePos))) {
        if (selected) {
            selected = false;
        }
        else {
            selected = true;
        }
        return true;
    }
    else {
        return false;
    }
}

bool MouseComponent::isSelected() {
    return selected;
}

bool MouseComponent::isHover() {
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*GameEngine::getWindow());
    sf::Vector2f mousePos = GameEngine::getWindow()->mapPixelToCoords(mousePixel, GameEngine::getWindow()->getDefaultView()); 
    
    sf::FloatRect bounds(
        {owner->getPosition().x,
        owner->getPosition().y},
        {owner->getSize().x,
        owner->getSize().y}
    );
    if (bounds.contains(sf::Vector2f(mousePos))) {
        return true;
    }
    return false;
}

void MouseComponent::setSelected(bool _selected) {
    selected = _selected;
}
