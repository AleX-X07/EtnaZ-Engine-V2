#include "RenderTextComponent.h"

#include "../../Object.h"
#include "../../../Main/GameEngine.h"

RenderTextComponent::RenderTextComponent(Object* _owner, std::string _path) : RenderTextComponent(_owner, _path, 25, sf::Color::White) {
}

RenderTextComponent::RenderTextComponent(Object* _owner, std::string _path, int _characterSize) : RenderTextComponent(_owner, _path, _characterSize, sf::Color::White){
}

RenderTextComponent::RenderTextComponent(Object* _owner, std::string _path, int _characterSize, sf::Color _color) : Component(_owner), path(_path) {
    isActive = true;
    
    myFont = new sf::Font(path);
    if (myFont) {
        myText = new sf::Text(*myFont);
        myText->setCharacterSize(_characterSize);
        myText->setFillColor(_color);
    }
    else {
        myFont = nullptr;
        myText = nullptr;
    }
}

RenderTextComponent::~RenderTextComponent() {
    delete myText;
    myText = nullptr;
}

void RenderTextComponent::setText(std::string _text) {
    myText->setString(_text);
}

void RenderTextComponent::setVisibility(bool _visible) {
    isActive = _visible;
}

void RenderTextComponent::update(float& deltaTime) {
    myText->setPosition(owner->getPosition());
}

void RenderTextComponent::render() {
    if (isActive) {
        GameEngine::getWindow()->draw(*myText);
    }
}
