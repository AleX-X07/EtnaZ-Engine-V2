#include "Dev.h"

#include "Main/GameEngine.h"
#include "Object/Component/Graphics/RenderComponent.h"

Dev::Dev() {
    GameEngine::setCurrentScene(new Scene());
    
    Object* newObj = new Object({1920,15},{0,0});
    newObj->addComponent(new RenderComponent(newObj,sf::Color(128,128,128)));
    
    GameEngine::getCurrentScene()->addObjectInScene(newObj);    
}
