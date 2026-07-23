#include "ToolBarreMenuComponent.h"

#include "../../../Object.h"
#include "../../Periph/MouseComponent.h"

ToolBarreMenuComponent::ToolBarreMenuComponent(Object* _owner) : Component(_owner){
}

ToolBarreMenuComponent::~ToolBarreMenuComponent() {
    for (auto& o : myObjects) {
        delete o;
        o = nullptr;
    }
}

void ToolBarreMenuComponent::addInMenu(Object* obj) {
    float posX = owner->getPosition().x;
    float posY = 0;
    if (myObjects.empty()) {
        posY = owner->getPosition().y + owner->getSize().y;
    }
    else {
        auto* lastObj = myObjects.back();
        posY = lastObj->getPosition().y + lastObj->getSize().y;
    }
    obj->setPosition({posX, posY});
    myObjects.push_back(obj);
}

std::vector<Object*>& ToolBarreMenuComponent::getMyObjects() {
    return myObjects;
}

void ToolBarreMenuComponent::update(float& deltaTime) {
    auto* mouse = owner->getComponent<MouseComponent>();
    mouse->isClicked();
    if (mouse->isSelected()) {
        for (auto& o : myObjects) {
            o->update(deltaTime);
        }
        if (Input::getInstance()->isMousePressed(sf::Mouse::Button::Left)) {
            bool clickedInside = mouse->isHover();
            if (!clickedInside) {
                for (auto& o : myObjects) {
                    auto* comp = o->getComponent<MouseComponent>();
                    if (comp && comp->isHover()) {
                        clickedInside = true;
                        break;
                    }
                }
            }
            if (!clickedInside) {
                mouse->setSelected(false);
            }
        }
    }
}

void ToolBarreMenuComponent::render() {
    auto* mouse = owner->getComponent<MouseComponent>();
    if (mouse && mouse->isSelected()) {
        for (auto& o : myObjects) {
            o->render();
        }
    }
}
