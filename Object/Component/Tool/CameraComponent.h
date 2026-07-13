#pragma once
#include "../Component.h"

class CameraComponent final : public Component {
private:
    sf::View* myView;
    sf::FloatRect* rect;
    
public:
    CameraComponent(Object* _owner, sf::FloatRect* _rect);
    virtual ~CameraComponent() override;
};
