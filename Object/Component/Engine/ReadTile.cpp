#include "ReadTile.h"
#include "../../Object.h"
#include "../../../Main/GameEngine.h"
#include "../Graphics/RenderComponent.h"
#include "../Periph/MouseComponent.h"

ReadTile::ReadTile(Object* _owner, std::string _path, int nbrColonne) : Component(_owner), path(_path){
    currentSelected = nullptr;
    tileSelected = nullptr;
    tileSelect = false;
    
    offsetImage = owner->getSize().x / nbrColonne / 8 * 2;
    int currentColonne = 0;
    int currentLigne = 0;
    
    sf::Vector2f _sizeImage = {owner->getSize().x / nbrColonne - offsetImage,owner->getSize().x / nbrColonne - offsetImage};
    
    float X = owner->getPosition().x + offsetImage;
    float Y = (owner->getPosition().y + offsetImage);
    
    Object* addImage = new Object(owner->getCurrentScene(), {_sizeImage.x, _sizeImage.y/2}, {X,Y});
    addImage->addComponent(new RenderComponent(addImage, sf::Color::Black));
    myButtons.push_back(addImage);
    
    currentLigne++;
    Y = (owner->getPosition().y + offsetImage) + ((_sizeImage.y + offsetImage)*currentLigne);
    
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

void ReadTile::tileDisplay() {
    if (tileSelected != nullptr) {
        currentSelected = new sf::RectangleShape({tileSelected->getSize().x + offsetImage/2,tileSelected->getSize().y + offsetImage/2});
        currentSelected->setPosition({tileSelected->getPosition().x - offsetImage/4,tileSelected->getPosition().y - offsetImage/4});
        currentSelected->setFillColor({0,0,0,125});
        tileSelect = true;
    }
    else {
        delete currentSelected;
        currentSelected = nullptr;
        tileSelect = false;
    }
}

void ReadTile::update(float& deltaTime) {
    for (auto& b : myButtons) {
        b->update(deltaTime);
    }
    tileDisplay();
    for (auto& t : myTiles) {
        if (t->hasComponent<MouseComponent>()) {
            if (t->getComponent<MouseComponent>()->isClicked()) {
                if (tileSelected != t) {
                    delete currentSelected;
                    currentSelected = nullptr;
                    tileSelected = t;
                }
                else {
                    tileSelected = nullptr;
                }
            }
        }
        t->update(deltaTime);
    }
}

void ReadTile::render() {
    for (auto& b : myButtons) {
        b->render();
    }
    if (currentSelected != nullptr && tileSelect) {
        GameEngine::getWindow()->draw(*currentSelected);
    }
    for (auto& t : myTiles) {
        t->render();
    }
}
