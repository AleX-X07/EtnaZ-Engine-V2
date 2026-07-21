#include "DragComponent.h"

#include "../../../Tool/Input.h"
#include "../../../Main/GameEngine.h"

DragComponent::DragComponent(Object* _owner) : Component(_owner), isDragging(false) {
}

bool DragComponent::getIsDragging() {
    return isDragging;
}

void DragComponent::update(float& deltaTime) {
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*GameEngine::getWindow());
    sf::Vector2f mousePos = GameEngine::getWindow()->mapPixelToCoords(mousePixel, GameEngine::getWindow()->getDefaultView());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        if (isDragging) {
            sf::Vector2f delta = mousePos - lastMousePos;
            owner->setPosition(owner->getPosition() - delta);
        }
        isDragging = true;
        lastMousePos = mousePos;
    }
    else {
        isDragging = false;
    }
}
