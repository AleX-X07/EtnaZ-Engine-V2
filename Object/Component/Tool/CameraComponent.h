#pragma once
#include "../Component.h"
#include "../../../Globals.h"

class GameEngine;

class CameraComponent final : public Component {
private:
    sf::View* myView;
    sf::FloatRect* rect;
    
    bool zoom;
    
public:
    CameraComponent(Object* _owner, sf::FloatRect* _rect);
    CameraComponent(Object* _owner, sf::FloatRect* _rect, bool _zoom);
    virtual ~CameraComponent() override;
    sf::View* getView();
    void setZoom(float fact);
    
    virtual void update(float& deltaTime) override;
};
