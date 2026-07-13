#include "CameraComponent.h"

CameraComponent::CameraComponent(Object* _owner, sf::FloatRect* _rect) : Component(_owner), rect(_rect){
    myView = new sf::View(*rect);
}

CameraComponent::~CameraComponent() {
    delete myView;
    myView = nullptr;
}
