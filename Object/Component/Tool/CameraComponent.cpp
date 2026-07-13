#include "CameraComponent.h"
#include "../../../Main/GameEngine.h"

CameraComponent::CameraComponent(Object* _owner, sf::FloatRect* _rect) : Component(_owner), rect(_rect){
    myView = new sf::View(*rect);
}

CameraComponent::~CameraComponent() {
    delete myView;
    myView = nullptr;
}

void CameraComponent::update(float& deltaTime) {
    sf::Vector2f ObjectivePos = { owner->getPosition().x + owner->getSize().x / 2, owner->getPosition().y + owner->getSize().y / 2 };
        
    ObjectivePos.x = std::max(screen.x / 2, std::min(ObjectivePos.x, level.x - screen.x / 2));
    ObjectivePos.y = std::max(screen.y / 2, std::min(ObjectivePos.y, level.y - screen.y / 2));
        
    rect->position = ObjectivePos;
    myView->setCenter(rect->position);
    GameEngine::getWindow()->setView(*myView);
}
