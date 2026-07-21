#pragma once
#include "../Component.h"

class Input;
class GameEngine;

class DragComponent final : public Component {
private:
    sf::Vector2f lastMousePos;
    bool isDragging;

public:
    DragComponent(Object* _owner);
    virtual ~DragComponent() override = default;
    
    bool getIsDragging();
    
    virtual void update(float& deltaTime) override;
};
