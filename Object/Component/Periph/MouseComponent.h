#pragma once
#include "../Component.h"
#include "../../../Tool/Input.h"

class GameEngine;

class MouseComponent final : public Component {
private:
    bool selected;
    
public:
    MouseComponent(Object* _owner);
    virtual ~MouseComponent() override = default;
    
    virtual void update(float& deltaTime) override;
    
    sf::Vector2i getMousePosition();
    bool isClicked();
    bool isSelected();
    bool isHover();
    
    void setSelected(bool _selected);
};
