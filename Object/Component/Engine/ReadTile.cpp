#include "ReadTile.h"
#include "../../Object.h"
#include "../Graphics/RenderComponent.h"
#include "../Periph/MouseComponent.h"

ReadTile::ReadTile(Object* _owner, std::string _path, sf::Vector2f _sizeImage) : Component(_owner), path(_path){
    float X = owner->getPosition().x + 10;
    float Y = owner->getPosition().y + 30;
    int nbrColonne = 2;
    int currentColonne = 0;
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    else {
        for (auto& i : std::filesystem::directory_iterator(path)) {
            if (i.path().extension() == ".png") {
                Object* obj = new Object(owner->getCurrentScene(),{X,Y},_sizeImage);
                obj->addComponent(new RenderComponent(obj,path));
                obj->addComponent(new MouseComponent(obj));
                currentColonne++;
                if (currentColonne >= nbrColonne) {
                    currentColonne = 0;
                    Y = Y + _sizeImage.y + 30;
                }
                X = X + _sizeImage.x + 10;
                myTiles.push_back(obj);
            }
        }
    }
}

ReadTile::~ReadTile() {
    for (auto t : myTiles) {
        delete t;
        t = nullptr;
    }
    myTiles.clear();
}

void ReadTile::update(float& deltaTime) {
    for (auto& t : myTiles) {
        t->update(deltaTime);
    }
}

void ReadTile::render() {
    for (auto& t : myTiles) {
        t->render();
    }
}
