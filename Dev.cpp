#include "Dev.h"

#include "Main/GameEngine.h"
#include "Object/Component/Engine/ReadTile.h"
#include "Object/Component/Graphics/RenderComponent.h"
#include "ViewIsometrique/IsoComponent.h"
#include "ViewIsometrique/IsoDisplay.h"

Dev::Dev() {
    Scene* scene = new Scene();
    scene->getLayer()->setNbrLayer(3);
    GameEngine::setCurrentScene(scene);
    
    // Object* newObj = new Object(scene,{1920,15},{0,0});
    // newObj->addComponent(new RenderComponent(newObj,sf::Color(128,128,128)));
    
    // Vu ISO Test //
    // --> besoin de trouver un moyen pour que les offset s'adapte en fonction de l'image
    
    // IsoUtils::getInstance()->setTileSize({128,64});
    // IsoUtils::getInstance()->setOrigin({640,360});
    //
    // Object* newObj2 = new Object(scene);
    // newObj2->addComponent(new IsoDisplay(newObj2));
    //
    // GameEngine::getCurrentScene()->addObjectInScene(newObj2);
    //
    // int nbrCase = 2;
    // float offsetY = 0;
    // float offsetX = 0;
    //
    // for (int X = -nbrCase; X < nbrCase; X++) {
    //     offsetY = 0;
    //     for (int Y = -nbrCase; Y < nbrCase; Y++) {
    //         Object* newObj3 = new Object(scene,{128,64},{100,100});
    //         newObj3->addComponent(new RenderComponent(newObj3, "Assets/test2.png"));
    //         newObj3->getComponent<RenderComponent>()->getRect()->setOrigin({newObj3->getSize().x / 2.f, newObj3->getSize().y / 2.f - offsetY - offsetX});
    //         newObj3->addComponent(new IsoComponent(newObj3, {X,Y}));   
    //         GameEngine::getCurrentScene()->addObjectInScene(newObj3);
    //         offsetY-=10;
    //     }
    //     offsetX-=10;
    // }
    
    
    for (int X = 0; X < level.x/128; X++) {
        for (int Y = 0; Y < level.y/128; Y++) {
            Object* newObj = new Object(scene,{128,128},{128*float(X),128*float(Y)});
            newObj->addComponent(new RenderComponent(newObj,sf::Color(0,0,0,255)));
            newObj->getComponent<RenderComponent>()->getRect()->setOutlineColor({255,255,255});
            newObj->getComponent<RenderComponent>()->getRect()->setOutlineThickness(2);
            GameEngine::getCurrentScene()->addObjectInScene(newObj,0);
        }
    }
    
    Object* newObj = new Object(scene,{screen.x,15},{0,0});
    newObj->addComponent(new RenderComponent(newObj,sf::Color(0,128,128)));
    GameEngine::getCurrentScene()->addObjectInScene(newObj,2);
    
    Object* newObj2 = new Object(scene,{screen.x/4,screen.y},{0,0});
    newObj2->addComponent(new RenderComponent(newObj2,sf::Color(128,128,128)));
    newObj2->addComponent(new ReadTile(newObj2, "Engine/Image",{128,128}));
    GameEngine::getCurrentScene()->addObjectInScene(newObj2,1);
}
