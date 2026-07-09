#include "RenderComponent.h"

#include "../../Object.h"
#include "../../../Main/GameEngine.h"

RenderComponent::RenderComponent(Object* _owner, std::string _path) : Component(_owner) {
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

RenderComponent::RenderComponent(Object* _owner, sf::Color _color) : Component(_owner) {
    color = &_color;
    texture = nullptr;
    
    rect = new sf::RectangleShape(owner->getSize());
    rect->setPosition(owner->getPosition());
    
    rect->setFillColor(*color);
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

sf::Texture* RenderComponent::getTexture() {
    return texture;
}

sf::Color* RenderComponent::getColor() {
    return color;
}


void RenderComponent::update(float& deltaTime) {
    rect->setPosition(owner->getPosition());
}

void RenderComponent::render() {
    GameEngine::getWindow()->draw(*rect);
}
