#pragma once
#include "../Component.h"
#include "../../../Globals.h"

class GameEngine;

class CameraComponent final : public Component {
private:
    sf::View* myView;
    sf::FloatRect* rect;
    
public:
    CameraComponent(Object* _owner, sf::FloatRect* _rect);
    virtual ~CameraComponent() override;
    
    virtual void update(float& deltaTime) override;
};
