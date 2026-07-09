#pragma once
#include "../Object/Component/Component.h"
#include "../ViewIsometrique/IsoUtils.h"
#include "IsoDisplay.h"

class IsoComponent final : public Component{
private:
    sf::Vector2i gridPos;
    
public:
    IsoComponent(Object* _owner,sf::Vector2i gridPos);
    virtual ~IsoComponent() override = default;
    
    int getDepth();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
