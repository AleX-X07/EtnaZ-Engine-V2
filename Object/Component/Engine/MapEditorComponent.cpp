#include "MapEditorComponent.h"

#include "../../../Main/GameEngine.h"
#include "../Graphics/RenderComponent.h"
#include "../Tool/CameraComponent.h"

MapEditorComponent::MapEditorComponent(Object* _owner) : Component(_owner){
    myLayer = new Layer();
    myLayer->setNbrLayer(1);
    
    camera = new Object(GameEngine::getCurrentScene(), {screen.x/4*3,screen.y-15/2}, {owner->getPosition().x + owner->getSize().x/2, owner->getPosition().y + owner->getSize().y/2});
    sf::FloatRect camRect(
    {owner->getPosition().x, owner->getPosition().y},
    {owner->getSize().x, owner->getSize().y}
    );
    camera->addComponent(new CameraComponent(camera, &camRect));
    
    for (int X = 0; X < level.x/128; X++) {
        for (int Y = 0; Y < level.y/128; Y++) {
            Object* newObj = new Object(GameEngine::getCurrentScene(),{128,128},{128*float(X),128*float(Y)});
            newObj->addComponent(new RenderComponent(newObj,sf::Color(0,0,0,255)));
            newObj->getComponent<RenderComponent>()->getRect()->setOutlineColor({255,255,255});
            newObj->getComponent<RenderComponent>()->getRect()->setOutlineThickness(2);
            socketTiles.push_back(newObj);
            myLayer->addInLayer(newObj, 0);
        }
    }
}

MapEditorComponent::~MapEditorComponent() {
    delete myLayer;
    myLayer = nullptr;
    
    for (auto& sT : socketTiles) {
        delete sT;
        sT = nullptr;
    }
    socketTiles.clear();
}

void MapEditorComponent::update(float& deltaTime) {
    for (auto& sT : socketTiles) {
        sT->update(deltaTime);
    }
    camera->setPosition({camera->getPosition().x + 50 * deltaTime, camera->getPosition().y});
}

void MapEditorComponent::render() {
    myLayer->render();
}
