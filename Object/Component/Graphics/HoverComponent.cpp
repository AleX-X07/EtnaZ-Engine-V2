#include "HoverComponent.h"

#include "../../Object.h"
#include "../../../Main/GameEngine.h"
#include "../Periph/MouseComponent.h"

HoverComponent::HoverComponent(Object* _owner, sf::Color _color) : Component(_owner) {
    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    
    myTexture = nullptr;
    outLineTickness = 0;
    
    color = _color;
    outlineColor = sf::Color::Black;
    
    rect->setFillColor(color);
    
    isActive = false;
}

HoverComponent::HoverComponent(Object* _owner, std::string _path) : Component((_owner)){
    outLineTickness = 0;
    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    path = _path;
    
    myTexture = new sf::Texture(path);
    
    if (myTexture) {
        rect->setTexture(myTexture);
    }
    
    color = sf::Color::Black;
    outlineColor = sf::Color::Black;
    
    isActive = false;
}

HoverComponent::HoverComponent(Object* _owner, int _outlineTicknes, sf::Color _color) : Component(_owner) {
    outLineTickness = _outlineTicknes;
    
    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    
    myTexture = nullptr;
    color = sf::Color::Black;
    outlineColor = _color;
    rect->setOutlineThickness(outLineTickness);
    rect->setOutlineColor(outlineColor);
    
    isActive = false;
}

HoverComponent::~HoverComponent() {
    delete rect;
    rect = nullptr;
}

void HoverComponent::setTexture(sf::Texture* newTexture) {
    myTexture = newTexture;
    rect->setTexture(myTexture);
}

void HoverComponent::setColor(sf::Color newColor) {
    color = newColor;
    rect->setFillColor(color);
}

void HoverComponent::setOutlineTickness(int _newOutlineTicknes) {
    outLineTickness = _newOutlineTicknes;
    rect->setOutlineThickness(outLineTickness);
}

void HoverComponent::setOutlineColor(sf::Color _newOutlineColor) {
    outlineColor = _newOutlineColor;
    rect->setOutlineColor(_newOutlineColor);
}

sf::Texture* HoverComponent::getTexture() {
    return myTexture;
}

sf::Color& HoverComponent::getColor() {
    return color;
}

int HoverComponent::getOutlineTickness() {
    return outLineTickness;
}

sf::Color& HoverComponent::getOutlineColor() {
    return outlineColor;
}

void HoverComponent::update(float& deltaTime) {
    if (owner->hasComponent<MouseComponent>()) {
        if (owner->getComponent<MouseComponent>()->isHover()) {
            isActive = true;
        }
        else {
            isActive = false;
        }
    }
}

void HoverComponent::render() {
    if (isActive) {
        GameEngine::getWindow()->draw(*rect);
    }
}
