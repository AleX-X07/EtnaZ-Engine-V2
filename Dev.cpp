#include "Dev.h"

#include "Main/GameEngine.h"
#include "Object/Component/Engine/FillTileComponent.h"
#include "Object/Component/Engine/MapEditorComponent.h"
#include "Object/Component/Engine/ReadTileComponent.h"
#include "Object/Component/Engine/ToolBarreComponent.h"
#include "Object/Component/Graphics/RenderComponent.h"
#include "Object/Component/Periph/MouseComponent.h"
#include "ViewIsometrique/IsoComponent.h"
#include "ViewIsometrique/IsoDisplay.h"

Dev::Dev() {
    Scene* scene = new Scene();
    scene->getLayer()->setNbrLayer(3);
    GameEngine::setCurrentScene(scene);
    
    Object* map = new Object(scene, editorWindowSize,editorWindowPos);
    map->addComponent(new MouseComponent(map));
    map->addComponent(new MapEditorComponent(map));
    map->addComponent(new FillTileComponent(map));
    GameEngine::getCurrentScene()->addObjectInScene(map,0);
    
    Object* toolBarre = new Object(scene,{screen.x,15},{0,0});
    toolBarre->addComponent(new RenderComponent(toolBarre,sf::Color(0,128,128)));
    toolBarre->addComponent(new ToolBarreComponent(toolBarre));
    GameEngine::getCurrentScene()->addObjectInScene(toolBarre,2);
    
    Object* panneauLateral = new Object(scene,readerWindowSize,readerWindowPos);
    panneauLateral->addComponent(new RenderComponent(panneauLateral,sf::Color(128,128,128)));
    panneauLateral->addComponent(new ReadTileComponent(panneauLateral, "Engine/Image",4));
    GameEngine::getCurrentScene()->addObjectInScene(panneauLateral,1);
}

