#include "MapEditorComponent.h"

#include "FillTileComponent.h"
#include "../../../Main/GameEngine.h"
#include "../Graphics/RenderComponent.h"
#include "../Periph/DragComponent.h"
#include "../Periph/MouseComponent.h"
#include "../Tool/CameraComponent.h"

MapEditorComponent::MapEditorComponent(Object* _owner) : Component(_owner) {
    myLayer = new Layer();
    myLayer->setNbrLayer(1);
    
    camera = new Object(GameEngine::getCurrentScene(), owner->getSize(), owner->getPosition());
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
            newObj->addComponent(new MouseComponent(newObj));
            newObj->addComponent(new RenderComponent(newObj,"Assets/Socket.png"));
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

std::vector<Object*>& MapEditorComponent::getSocketTiles() {
    return socketTiles;
}

std::vector<Object*>& MapEditorComponent::getObjectsAdd() {
    return objectsAdd;
}

Layer* MapEditorComponent::getLayer() {
    return myLayer;
}

Object* MapEditorComponent::getCamera() {
    return camera;
}

void MapEditorComponent::deleteTile(Object* tileToRemove) {
    surface->draw(*tileToRemove->getComponent<RenderComponent>()->getRect());
    surface->display();
    delete sprite;
    sprite = new sf::Sprite(surface->getTexture());
}

void MapEditorComponent::update(float& deltaTime) {
    if (camera) {
        auto* cam = camera->getComponent<CameraComponent>();
        auto* mouse = owner->getComponent<MouseComponent>();
        if (mouse) {
            if (mouse->isHover()) {
                camera->update(deltaTime);   
            }
        }
        if (cam) {
            cam->setView();   
        }
    }
}

void MapEditorComponent::render() {
    if (sprite && myLayer && camera) {
        GameEngine::getWindow()->draw(*sprite);
        myLayer->render();
        camera->render();
        GameEngine::getWindow()->setView(GameEngine::getWindow()->getDefaultView());   
    }
}
