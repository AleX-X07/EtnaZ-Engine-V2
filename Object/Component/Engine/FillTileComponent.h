#pragma once
#include "../Component.h"

class Object;
class ReadTileComponent;
class MapEditorComponent;
class Scene;

class FillTileComponent final : public Component {
private:
    
public:
    FillTileComponent(Object* _owner);
    virtual ~FillTileComponent() override = default;
    
    void addTile(Object* target, ReadTileComponent* readTile, MapEditorComponent* mapEditor, Scene* currentScene);
    void removeTile(ReadTileComponent* readTile, MapEditorComponent* mapEditor, Scene* currentScene);
    
    virtual void update(float& deltaTime) override;
};
