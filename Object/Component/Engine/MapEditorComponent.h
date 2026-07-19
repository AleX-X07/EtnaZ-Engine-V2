#pragma once
#include "../Component.h"
#include "../../../Globals.h"

class Layer;

class MapEditorComponent final : public Component {
private:
    std::vector<Object*> socketTiles;
    Layer* myLayer;
    Object* camera;
    
public:
    MapEditorComponent(Object* _owner);
    virtual ~MapEditorComponent() override;
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
