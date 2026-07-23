#pragma once
#include "../../Component.h"

class ToolBarreMenuComponent final : public Component {
private:
    std::vector<Object*> myObjects;
    
public:
    ToolBarreMenuComponent(Object* _owner);
    virtual ~ToolBarreMenuComponent() override;
    
    void addInMenu(Object* obj);
    std::vector<Object*>& getMyObjects();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
