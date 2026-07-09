#include "IsoComponent.h"

#include "../Object/Object.h"

IsoComponent::IsoComponent(Object* _owner, sf::Vector2i _gridPos) : Component(_owner), gridPos(_gridPos){
}

int IsoComponent::getDepth() {
    return gridPos.x + gridPos.y;
}

void IsoComponent::update(float& deltaTime) {
    owner->setPosition(IsoUtils::getInstance()->gridToScreen(gridPos));
}

void IsoComponent::render() {
}
