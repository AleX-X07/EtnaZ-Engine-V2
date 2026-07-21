#include "MapEditorComponent.h"

#include "../../../Main/GameEngine.h"
#include "../Graphics/RenderComponent.h"
#include "../Periph/DragComponent.h"
#include "../Periph/MouseComponent.h"
#include "../Tool/CameraComponent.h"

MapEditorComponent::MapEditorComponent(Object* _owner) : Component(_owner) {
    myLayer = new Layer();
    myLayer->setNbrLayer(1);
    
    camera = new Object(GameEngine::getCurrentScene(), {screen.x/4*3,screen.y-15}, {screen.x/4, 15});
    camRect = new sf::FloatRect(
    {camera->getPosition().x, camera->getPosition().y},
    {camera->getSize().x, camera->getSize().y}
    );
    camera->addComponent(new DragComponent(camera));
    camera->addComponent(new CameraComponent(camera, camRect, true));
    
    surface = new sf::RenderTexture(sf::Vector2u(level.x, level.y));
    surface->clear(sf::Color::Transparent);
    for (int X = 0; X < level.x/128; X++) {
        for (int Y = 0; Y < level.y/128; Y++) {
            Object* newObj = new Object(GameEngine::getCurrentScene(),{128,128},{128*float(X),128*float(Y)});
            newObj->addComponent(new RenderComponent(newObj,sf::Color(0,0,0,255)));
            newObj->getComponent<RenderComponent>()->getRect()->setOutlineColor({255,255,255});
            newObj->getComponent<RenderComponent>()->getRect()->setOutlineThickness(2);
            socketTiles.push_back(newObj);
            surface->draw(*newObj->getComponent<RenderComponent>()->getRect());
        }
    }
    surface->display();
    sprite = new sf::Sprite(surface->getTexture());
}

MapEditorComponent::~MapEditorComponent() {
    delete myLayer;
    myLayer = nullptr;
    
    for (auto& sT : socketTiles) {
        delete sT;
        sT = nullptr;
    }
    socketTiles.clear();
    
    delete camRect;
    camRect = nullptr;
    
    delete surface;
    surface = nullptr;
    
    delete sprite;
    sprite = nullptr;
}

void MapEditorComponent::update(float& deltaTime) {
    for (auto& sT : socketTiles) {
        sT->update(deltaTime);
    }
    camera->update(deltaTime);
}

void MapEditorComponent::render() {
    GameEngine::getWindow()->draw(*sprite);
    myLayer->render();
    camera->render();
    GameEngine::getWindow()->setView(GameEngine::getWindow()->getDefaultView());
}
