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
    layerSelected = 0;
    
    offsetImage = owner->getSize().x / nbrColonne / 8 * 2;
    currentColonne = 0;
    currentLigne = 0;
    
    sizeImage = {owner->getSize().x / nbrColonne - offsetImage,owner->getSize().x / nbrColonne - offsetImage};
    
    X = owner->getPosition().x + offsetImage;
    Y = (owner->getPosition().y + offsetImage);
    
    sf::Vector2f sizeButton = {sizeImage.x, sizeImage.y/2};
    
    sf::Color transparentColor = {0,0,0,128};
    
    addImage = new Object(owner->getCurrentScene(), sizeButton, {X,Y});
    
    addImage->addComponent(new MouseComponent(addImage));
    addImage->addComponent(new RenderComponent(addImage, sf::Color::White));
    addImage->addComponent(new HoverComponent(addImage, transparentColor));
    addImage->addComponent(new RenderTextComponent(addImage, "Assets/Font/Brown_Cookies.otf", 12, sf::Color::Black));
    addImage->addComponent(new OpenFileExplorerComponent(addImage, path, {"png","jpg"}));
    
    addImage->getComponent<RenderComponent>()->setOutline(2);
    addImage->getComponent<RenderComponent>()->setOutlineColor(sf::Color::Black);
    addImage->getComponent<RenderTextComponent>()->setText("Add \n Image");
    
    X += sizeImage.x + offsetImage;
    removeImage = new Object(owner->getCurrentScene(), sizeButton, {X,Y});
    
    removeImage->addComponent(new MouseComponent(removeImage));
    removeImage->addComponent(new RenderComponent(removeImage, sf::Color::Red));
    removeImage->addComponent(new RenderTextComponent(removeImage, "Assets/Font/Brown_Cookies.otf", 12, sf::Color::Black));
    removeImage->addComponent(new HoverComponent(removeImage, transparentColor));
    
    removeImage->getComponent<RenderComponent>()->setOutline(2);
    removeImage->getComponent<RenderComponent>()->setOutlineColor(sf::Color::Black);
    removeImage->getComponent<RenderTextComponent>()->setText("Remove \n Image");
    
    currentLigne++;
    X = owner->getPosition().x + offsetImage;
    Y = (owner->getPosition().y + offsetImage) + ((sizeImage.y + offsetImage)*currentLigne);
    
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
        Object* obj = new Object(owner->getCurrentScene(), sizeImage, {X, Y});
        obj->addComponent(new RenderComponent(obj, _path.string()));
        obj->addComponent(new MouseComponent(obj));

        currentColonne++;
        if (currentColonne >= nbrColonne) {
            currentColonne = 0;
            currentLigne++;
            X = owner->getPosition().x + offsetImage;
            Y = (owner->getPosition().y + offsetImage) + ((sizeImage.y + offsetImage) * currentLigne);
        } else {
            X = X + sizeImage.x + offsetImage / 2;
        }

        myTiles.push_back(obj);
    }
}

void ReadTileComponent::removeDisplay() {
    auto* comp = removeImage->getComponent<MouseComponent>();
    auto* rend = removeImage->getComponent<RenderComponent>();
    if (comp && rend) {
        comp->isClicked();
        if (comp->isSelected()) {
            rend->setOutlineColor(sf::Color::Blue);
            delete currentSelected;
            currentSelected = nullptr;
            tileSelect = false;
            tileSelected = nullptr;
        }
        else {
            rend->setOutlineColor(sf::Color::Black);
        }
    }
}


std::string& ReadTileComponent::getPath() {
    return path;
}

Object* ReadTileComponent::getTileSelected() {
    return tileSelected;
}

int ReadTileComponent::getLayerSelected() {
    return layerSelected;
}

Object* ReadTileComponent::getRemove() {
    return removeImage;
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
    removeImage->update(deltaTime);
    removeDisplay();
    tileDisplay();
    for (auto& t : myTiles) {
        if (t->hasComponent<MouseComponent>()) {
            if (t->getComponent<MouseComponent>()->isClicked()) {
                auto* rend = removeImage->getComponent<RenderComponent>();
                auto* mouse = removeImage->getComponent<MouseComponent>();
                if (rend) {
                    mouse->setSelected(false);
                }
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
    removeImage->render();
    if (currentSelected != nullptr && tileSelect) {
        GameEngine::getWindow()->draw(*currentSelected);
    }
    for (auto& t : myTiles) {
        t->render();
    }
}
