#include "ToolBarreComponent.h"

#include "../../Object.h"
#include "../Dev/TestComponent.h"
#include "../Graphics/HoverComponent.h"
#include "../Graphics/RenderComponent.h"
#include "../Graphics/RenderTextComponent.h"
#include "../Periph/MouseComponent.h"
#include "ToolBarre/ToolBarreMenuComponent.h"

ToolBarreComponent::ToolBarreComponent(Object* _owner) : Component(_owner){
    auto* scene = owner->getCurrentScene();
    auto sizeY = owner->getSize().y;
    
    int sizeText = 15;
    
    sf::Color hoverColor = {0,0,0,128};
    
    
    // File
    sf::Vector2f sizeFile = {30,sizeY};
    std::vector<Component*> persoCompFile = {new TestComponent(nullptr), new TestComponent(nullptr)};
    std::unordered_map<std::string, sf::Vector2f> persoArgsFile = {{"Test", {500,sizeY}},{"Test2", {500,sizeY}}};
    myObjects.push_back(createButton(scene, sizeFile, "Assets/Font/Brown_Cookies.otf", "File",
        sizeText, sf::Color::Black, hoverColor, persoCompFile, persoArgsFile));
    
    // Settings
    sf::Vector2f sizeSettings = {60,sizeY};
    std::vector<Component*> persoCompSettings = {};
   std::unordered_map<std::string, sf::Vector2f> persoArgsSettings = {};
    myObjects.push_back(createButton(scene, sizeSettings, "Assets/Font/Brown_Cookies.otf", "Settings",
        sizeText, sf::Color::Black, hoverColor,persoCompSettings, persoArgsSettings));
}

ToolBarreComponent::~ToolBarreComponent() {
    for (auto& o : myObjects) {
        delete o;
        o = nullptr;
    }
    myObjects.clear();
}

sf::Vector2f ToolBarreComponent::getPosLastObj() {
    sf::Vector2f res;
    if (myObjects.empty()) {
        res = {0,0};
    }
    else {
        Object* obj = myObjects.back();
        res = {obj->getPosition().x + obj->getSize().x,0};
    }
    return res;
}

Object* ToolBarreComponent::createButton(Scene* scene, sf::Vector2f size, std::string _font, std::string _text, int sizeText, 
    sf::Color colorText, sf::Color colorhover, std::vector<Component*> persoComp, std::unordered_map<std::string, sf::Vector2f> persoArgs) {
    
    Object* newObj = new Object(scene, size,getPosLastObj());
    
    newObj->addComponent(new MouseComponent(newObj));
    newObj->addComponent(new RenderTextComponent(newObj, _font,sizeText,colorText));
    newObj->addComponent(new HoverComponent(newObj, colorhover));
    newObj->addComponent(new ToolBarreMenuComponent(newObj));
    
    auto* texFile = newObj->getComponent<RenderTextComponent>();
    texFile->setText(_text);
    auto* menuFile = newObj->getComponent<ToolBarreMenuComponent>();
    
    if (!persoComp.empty() && !persoArgs.empty()) {
        int currentComponent = 0;
        sf::Vector2f pos = {owner->getPosition().x,owner->getPosition().y};
        for (auto& [k,v] : persoArgs) {
            
            if (!menuFile->getMyObjects().empty()) {
                auto* obj = menuFile->getMyObjects().back();
                pos.y = obj->getPosition().y + obj->getSize().y;
            }
            else {
                pos.y = owner->getPosition().y + owner->getSize().y;
            }
            
            auto* rend = owner->getComponent<RenderComponent>();
            Object* newMenu = new Object(scene, v, pos);
            
            Component* comp = persoComp[currentComponent];
            comp->setOwner(newMenu);
            
            newMenu->addComponent(new MouseComponent(newMenu));
            newMenu->addComponent(new RenderComponent(newMenu,*rend->getColor()));
            newMenu->addComponent(new RenderTextComponent(newMenu,_font, sizeText,colorText));
            newMenu->addComponent(new HoverComponent(newMenu, colorhover));
            newMenu->addComponent(comp);
            
            auto* text = newMenu->getComponent<RenderTextComponent>();
            text->setText(k);
            
            menuFile->addInMenu(newMenu);
            
            currentComponent++;
        }
    }
    
    return newObj;
}

void ToolBarreComponent::update(float& deltaTime) {
    for (auto& o : myObjects) {
        o->update(deltaTime);
    }
}

void ToolBarreComponent::render() {
    for (auto& o : myObjects) {
        o->render();
    }
}
