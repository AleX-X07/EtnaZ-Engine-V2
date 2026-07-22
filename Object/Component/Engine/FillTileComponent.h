#pragma once
#include "../Component.h"

class FillTileComponent final : public Component {
private:
    
public:
    FillTileComponent(Object* _owner);
    virtual ~FillTileComponent() override = default;
    
    virtual void update(float& deltaTime) override;
};
