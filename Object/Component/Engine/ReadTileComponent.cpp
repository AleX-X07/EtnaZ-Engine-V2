#include "ReadTileComponent.h"
#include "../../Object.h"
#include "../../../Main/GameEngine.h"
#include "../Graphics/HoverComponent.h"
#include "../Graphics/RenderComponent.h"
#include "../Graphics/RenderTextComponent.h"
#include "../Periph/MouseComponent.h"
#include "../Engine/OpenFileExplorerComponent.h"

ReadTileComponent::ReadTileComponent(Object* _owner, std::string _path, int _nbrColonne) : Component(_owner), path(_path){
    nbrColonne = _nbrColonne;
    currentSelected = nullptr;
    tileSelected = nullptr;
    tileSelect = false;
    
    offsetImage = owner->getSize().x / nbrColonne / 8 * 2;
    currentColonne = 0;
    currentLigne = 0;
    
    _sizeImage = {owner->getSize().x / nbrColonne - offsetImage,owner->getSize().x / nbrColonne - offsetImage};
    
    X = owner->getPosition().x + offsetImage;
    Y = (owner->getPosition().y + offsetImage);
    
    addImage = new Object(owner->getCurrentScene(), {_sizeImage.x, _sizeImage.y/2}, {X,Y});
    addImage->addComponent(new MouseComponent(addImage));
    addImage->addComponent(new RenderComponent(addImage, sf::Color::White));
    addImage->getComponent<RenderComponent>()->setOutline(5);
    addImage->getComponent<RenderComponent>()->setOutlineColor(sf::Color::Black);
    addImage->addComponent(new HoverComponent(addImage, sf::Color::Green));
    addImage->getComponent<HoverComponent>()->setOutlineTickness(5);
    addImage->getComponent<HoverComponent>()->setOutlineColor(sf::Color::Red);
    addImage->addComponent(new RenderTextComponent(addImage, "Engine/Font/Brown_Cookies.otf", 12, sf::Color::Black));
    addImage->getComponent<RenderTextComponent>()->setText("Add \n Image");
    addImage->addComponent(new OpenFileExplorerComponent(addImage, path, {"png","jpg"}));
    
    currentLigne++;
    Y = (owner->getPosition().y + offsetImage) + ((_sizeImage.y + offsetImage)*currentLigne);
    
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    else {
        for (auto& i : std::filesystem::directory_iterator(path)) {
            if (addImage->hasComponent<OpenFileExplorerComponent>()) {
                auto* comp = addImage->getComponent<OpenFileExplorerComponent>();
                if (comp->isExtensionCompatible(i.path().extension().string())) {
                    addTileFromFile(i.path());
                }
            }
        }
    }
}

ReadTileComponent::~ReadTileComponent() {
    for (auto t : myTiles) {
        delete t;
        t = nullptr;
    }
    myTiles.clear();
}

void ReadTileComponent::tileDisplay() {
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

void ReadTileComponent::addTileFromFile(const std::filesystem::path& _path) {
    if (!_path.empty()) {
        Object* obj = new Object(owner->getCurrentScene(), _sizeImage, {X, Y});
        obj->addComponent(new RenderComponent(obj, _path.string()));
        obj->addComponent(new MouseComponent(obj));

        currentColonne++;
        if (currentColonne >= nbrColonne) {
            currentColonne = 0;
            currentLigne++;
            X = owner->getPosition().x + offsetImage;
            Y = (owner->getPosition().y + offsetImage) + ((_sizeImage.y + offsetImage) * currentLigne);
        } else {
            X = X + _sizeImage.x + offsetImage / 2;
        }

        myTiles.push_back(obj);
    }
}


std::string& ReadTileComponent::getPath() {
    return path;
}

void ReadTileComponent::update(float& deltaTime) {
    addImage->update(deltaTime);
    if (addImage->hasComponent<MouseComponent>()) {
        if (addImage->getComponent<MouseComponent>()->isClicked()) {
             if(addImage->hasComponent<OpenFileExplorerComponent>()) {
                 addTileFromFile(addImage->getComponent<OpenFileExplorerComponent>()->openFileExplorer());
             }
        }
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

void ReadTileComponent::render() {
    addImage->render();
    if (currentSelected != nullptr && tileSelect) {
        GameEngine::getWindow()->draw(*currentSelected);
    }
    for (auto& t : myTiles) {
        t->render();
    }
}
