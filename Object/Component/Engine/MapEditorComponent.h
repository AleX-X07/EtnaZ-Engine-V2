#pragma once
#include "../Component.h"
#include "../../../Globals.h"

class Layer;

class MapEditorComponent final : public Component {
private:
    std::vector<Object*> socketTiles;
    std::vector<Object*> objectsAdd;
    Layer* myLayer;
    Object* camera;
    sf::FloatRect* camRect;
    sf::RenderTexture* surface;
    sf::Sprite* sprite;
    
public:
    MapEditorComponent(Object* _owner);
    virtual ~MapEditorComponent() override;
    
    std::vector<Object*>& getSocketTiles();
    std::vector<Object*>& getObjectsAdd();
    Layer* getLayer();
    Object* getCamera();
    
    void deleteTile(Object* tileToRemove);
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
