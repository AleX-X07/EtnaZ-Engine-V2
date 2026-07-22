#include "FillTileComponent.h"

#include <X11/keysymdef.h>

#include "MapEditorComponent.h"
#include "ReadTileComponent.h"
#include "../../Object.h"
#include "../../../Main/GameEngine.h"
#include "../../../Scene/Scene.h"
#include "../Graphics/RenderComponent.h"
#include "../Periph/MouseComponent.h"
#include "../Tool/CameraComponent.h"

FillTileComponent::FillTileComponent(Object* _owner) : Component(_owner){
}

void FillTileComponent::update(float& deltaTime) {
    Object* target = nullptr;
    Scene* currentScene = owner->getCurrentScene();
    ReadTileComponent* readTile = nullptr;
    for (auto& obj : GameEngine::getCurrentScene()->getMyObjects()) {
        if (obj->hasComponent<ReadTileComponent>()) {
            readTile = obj->getComponent<ReadTileComponent>();
            break;
        }
    }
    auto* mapEditor = owner->getComponent<MapEditorComponent>();
    if (readTile && mapEditor) {
        target = readTile->getTileSelected();
        if (target) {
            for (auto& sT : mapEditor->getSocketTiles()) {
                auto* comp = sT->getComponent<MouseComponent>();
                if (comp) {
                    if (comp->isClicked(mapEditor->getCamera()->getComponent<CameraComponent>()->getView())) {
                        Object* newTile = new Object(currentScene,sT->getSize(), sT->getPosition());
                        auto* rend = target->getComponent<RenderComponent>();
                        newTile->addComponent(new RenderComponent(newTile, rend->getTexture()));
                        mapEditor->getObjectsAdd().push_back(newTile);
                        mapEditor->getLayer()->addInLayer(newTile, readTile->getLayerSelected());
                    }
                }
            }   
        }
    }
}
