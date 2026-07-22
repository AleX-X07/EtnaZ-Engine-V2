#include "RenderComponent.h"

#include "../../Object.h"
#include "../../../Main/GameEngine.h"

RenderComponent::RenderComponent(Object* _owner, std::string _path) : Component(_owner) {
    outlineTickness = 0;
    isActive = true;
    
    texture = new sf::Texture();
    color = nullptr;

    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    
    if (!texture->loadFromFile(_path)) {
        rect->setFillColor({255,255,255,255});
    }
    else {
        rect->setTexture(texture);
    }
}

RenderComponent::RenderComponent(Object* _owner, sf::Texture* _text) : Component(_owner) {
    outlineTickness = 0;
    isActive = true;
    
    texture = _text;
    color = nullptr;

    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    if (texture) {
        rect->setTexture(texture);
    }
}

RenderComponent::RenderComponent(Object* _owner, sf::Color _color) : Component(_owner) {
    outlineTickness = 0;
    isActive = true;
    
    color = new sf::Color(_color);
    texture = nullptr;
    
    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    
    rect->setFillColor(*color);
}

RenderComponent::RenderComponent(Object* _owner, int _outlineTickness, sf::Color _color) : Component(_owner) {
    isActive = true;
    
    color = nullptr;
    texture = nullptr;
    
    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    
    outlineTickness = _outlineTickness;
    outlineColor = _color;
    
    rect->setOutlineThickness(outlineTickness);
    rect->setOutlineColor(outlineColor);
}

RenderComponent::~RenderComponent() {
    delete rect;
    rect = nullptr;
    
    if (texture != nullptr) {
        delete texture;
        texture = nullptr;
    }
    
    if (color != nullptr) {
        delete color;
        color = nullptr;
    }
}

void RenderComponent::setTexture(sf::Texture* newTexture) {
    texture = newTexture;
    rect->setTexture(texture);
}

void RenderComponent::setColor(sf::Color newColor) {
    color = &newColor;
    rect->setFillColor(*color);
}

void RenderComponent::setOutline(int _newOutline) {
    outlineTickness = _newOutline;
    rect->setOutlineThickness(outlineTickness);
}

void RenderComponent::setOutlineColor(sf::Color _newColor) {
    outlineColor = _newColor;
    rect->setOutlineColor(outlineColor);
}

sf::RectangleShape* RenderComponent::getRect() {
    return rect;
}

sf::Texture* RenderComponent::getTexture() {
    return texture;
}

sf::Color* RenderComponent::getColor() {
    return color;
}

void RenderComponent::setVisibility(bool newVisibility) {
    isActive = newVisibility;
}


void RenderComponent::update(float& deltaTime) {
    rect->setPosition(owner->getPosition());
}

void RenderComponent::render() {
    if (isActive) {
        GameEngine::getWindow()->draw(*rect);
    }
}
