#include "Dev.h"

#include "Main/GameEngine.h"
#include "Object/Component/Engine/FillTileComponent.h"
#include "Object/Component/Engine/MapEditorComponent.h"
#include "Object/Component/Engine/ReadTileComponent.h"
#include "Object/Component/Graphics/RenderComponent.h"
#include "ViewIsometrique/IsoComponent.h"
#include "ViewIsometrique/IsoDisplay.h"

Dev::Dev() {
    Scene* scene = new Scene();
    scene->getLayer()->setNbrLayer(3);
    GameEngine::setCurrentScene(scene);
    
    Object* map = new Object(scene);
    map->addComponent(new MapEditorComponent(map));
    map->addComponent(new FillTileComponent(map));
    GameEngine::getCurrentScene()->addObjectInScene(map,0);
    
    Object* newObj = new Object(scene,{screen.x,15},{0,0});
    newObj->addComponent(new RenderComponent(newObj,sf::Color(0,128,128)));
    GameEngine::getCurrentScene()->addObjectInScene(newObj,2);
    
    Object* newObj2 = new Object(scene,{screen.x/4,screen.y},{0,15});
    newObj2->addComponent(new RenderComponent(newObj2,sf::Color(128,128,128)));
    newObj2->addComponent(new ReadTileComponent(newObj2, "Engine/Image",4));
    GameEngine::getCurrentScene()->addObjectInScene(newObj2,1);
}
