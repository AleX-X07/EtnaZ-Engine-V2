#include "CameraComponent.h"
#include "../../../Main/GameEngine.h"

CameraComponent::CameraComponent(Object* _owner, sf::FloatRect* _rect) : CameraComponent(_owner, _rect, false) {
}

CameraComponent::CameraComponent(Object* _owner, sf::FloatRect* _rect, bool _zoom) : Component(_owner), rect(_rect), zoom(_zoom) {
    myView = new sf::View(*rect);
}

CameraComponent::~CameraComponent() {
    delete myView;
    myView = nullptr;
}

sf::View* CameraComponent::getView() {
    return myView;
}

void CameraComponent::setZoom(float fact) {
    myView->zoom(fact);
}

void CameraComponent::update(float& deltaTime) {
    sf::Vector2f ObjectivePos = { owner->getPosition().x + owner->getSize().x / 2, owner->getPosition().y + owner->getSize().y / 2 };
        
    ObjectivePos.x = std::max(screen.x / 2, std::min(ObjectivePos.x, level.x - screen.x / 2));
    ObjectivePos.y = std::max(screen.y / 2, std::min(ObjectivePos.y, level.y - screen.y / 2));
        
    rect->position = ObjectivePos;
    myView->setCenter(rect->position);
    if (zoom) {
        float wheelDelta = Input::getInstance()->getWheelScrolled();
        if (wheelDelta != 0.f) {
            if (wheelDelta > 0) {
                setZoom(0.9f);                
            }
            else if (wheelDelta < 0) {
                setZoom(1.1f);
            }
        }
    }
    GameEngine::getWindow()->setView(*myView);
}


