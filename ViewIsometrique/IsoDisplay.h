#pragma once
#include "../Object/Component/Component.h"

class Scene;
class Object;
class IsoComponent;

class IsoDisplay final : public Component{
private:
    Scene* scene;
    
public:
    IsoDisplay(Object* _owner);
    virtual ~IsoDisplay() override = default;
    
    static bool compareDepth(Object* a, Object* b);
    
    virtual void render() override;
};
