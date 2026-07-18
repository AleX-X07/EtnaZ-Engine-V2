#include "RenderTextComponent.h"

#include "../../Object.h"
#include "../../../Main/GameEngine.h"

RenderTextComponent::RenderTextComponent(Object* _owner, std::string _path) : RenderTextComponent(_owner, _path, 25, sf::Color::White) {
}

RenderTextComponent::RenderTextComponent(Object* _owner, std::string _path, int _characterSize) : RenderTextComponent(_owner, _path, _characterSize, sf::Color::White){
}

RenderTextComponent::RenderTextComponent(Object* _owner, std::string _path, int _characterSize, sf::Color _color) : Component(_owner), path(_path) {
    sf::Font font(path);
    myText = new sf::Text(font);
    myText->setCharacterSize(_characterSize);
    myText->setFillColor(_color);
}

RenderTextComponent::~RenderTextComponent() {
    delete myText;
    myText = nullptr;
}

void RenderTextComponent::setText(std::string _text) {
    myText->setString(_text);
}

void RenderTextComponent::update(float& deltaTime) {
    myText->setPosition(owner->getPosition());
}

void RenderTextComponent::render() {
    GameEngine::getWindow()->draw(*myText);
}
