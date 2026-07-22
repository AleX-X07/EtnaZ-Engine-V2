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

FillTileComponent::FillTileComponent(Object* _owner) : Component(_owner), tileToRemove(nullptr){
}

void FillTileComponent::addTile(ReadTileComponent* readTile, MapEditorComponent* mapEditor, Scene* currentScene) {
        Object* target = nullptr;
        target = readTile->getTileSelected();
        if (target) {
            for (auto& sT : mapEditor->getSocketTiles()) {
                auto* comp = sT->getComponent<MouseComponent>();
                if (comp) {
                    auto* comp2 = owner->getComponent<MouseComponent>();
                    if (comp2) {
                        if (comp2->isClicked() && comp->isClicked(mapEditor->getCamera()->getComponent<CameraComponent>()->getView())) {
                            Object* newTile = new Object(currentScene,sT->getSize(), sT->getPosition());
                            auto* rend = target->getComponent<RenderComponent>();
                            newTile->addComponent(new RenderComponent(newTile, rend->getTexture()));
                            newTile->addComponent(new MouseComponent(newTile));
                            mapEditor->getObjectsAdd().push_back(newTile);
                            mapEditor->getLayer()->addInLayer(newTile, readTile->getLayerSelected());
                        }
                    }
                }
            }   
        }
    }

void FillTileComponent::removeTile(ReadTileComponent* readTile, MapEditorComponent* mapEditor,Scene* currentScene) {
    if (auto* click = readTile->getRemove()->getComponent<MouseComponent>()) {
        auto check = click->isSelected();
        if (check) {
            for (auto& sT : mapEditor->getSocketTiles()) {
                for (auto& oA : mapEditor->getObjectsAdd()) {
                    auto* comp = oA->getComponent<MouseComponent>();
                    auto* rend = oA->getComponent<RenderComponent>();
                    if (comp) {
                        if (comp->isClicked(mapEditor->getCamera()->getComponent<CameraComponent>()->getView())) {
                            rend->setVisibility(false);
                            tileToRemove = oA;
                        }
                    }
                }
            }   
        }
    }
}

void FillTileComponent::update(float& deltaTime) {
    Scene* currentScene = owner->getCurrentScene();
    ReadTileComponent* readTile = nullptr;
    for (auto& obj : GameEngine::getCurrentScene()->getMyObjects()) {
        if (obj->hasComponent<ReadTileComponent>()) {
            readTile = obj->getComponent<ReadTileComponent>();
            break;
        }
    }
    auto* mapEditor = owner->getComponent<MapEditorComponent>();
    if (tileToRemove) {
        auto* layer = mapEditor->getLayer();
        layer->removeInLayer(tileToRemove);
        auto& vec = mapEditor->getObjectsAdd();
        vec.erase(std::remove(vec.begin(), vec.end(), tileToRemove), vec.end());
        delete tileToRemove;
        tileToRemove = nullptr;
    }
    if (readTile && mapEditor) {
        addTile(readTile, mapEditor, currentScene);
        removeTile(readTile, mapEditor, currentScene);
    }
}
