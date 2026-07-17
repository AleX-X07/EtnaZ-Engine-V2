#include "ReadTile.h"
#include "../../Object.h"
#include "../Graphics/RenderComponent.h"
#include "../Periph/MouseComponent.h"

ReadTile::ReadTile(Object* _owner, std::string _path, int nbrColonne) : Component(_owner), path(_path){
    int offsetImage = owner->getSize().x / nbrColonne / 8 * 2;
    int currentColonne = 0;
    int currentLigne = 1;
    
    sf::Vector2f _sizeImage = {owner->getSize().x / nbrColonne - offsetImage,owner->getSize().x / nbrColonne - offsetImage};
    
    float X = owner->getPosition().x + offsetImage;
    float Y = (owner->getPosition().y + offsetImage) + ((_sizeImage.y + offsetImage)*currentLigne);
    
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    else {
        for (auto& i : std::filesystem::directory_iterator(path)) {
            if (i.path().extension() == ".png") {
                Object* obj = new Object(owner->getCurrentScene(),_sizeImage,{X,Y});
                obj->addComponent(new RenderComponent(obj,i.path().string()));
                obj->addComponent(new MouseComponent(obj));
                currentColonne++;
                if (currentColonne >= nbrColonne) {
                    currentColonne = 0;
                    currentLigne++;
                    X = owner->getPosition().x + offsetImage;
                    Y = (owner->getPosition().y + offsetImage) + ((_sizeImage.y + offsetImage)*currentLigne);
                }
                else {
                    X = X + _sizeImage.x + offsetImage/2;
                }
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
