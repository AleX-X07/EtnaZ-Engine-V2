#include "Scene.h"

Scene::Scene() : Scene(0){
}

Scene::Scene(int _idScene) {
    myLayer = new Layer();
    idScene = _idScene;
}

Scene::~Scene() {
    for (auto& object : myObjects) {
        delete object;
        object = nullptr;
    }
    myObjects.clear();
    
    delete myLayer;
    myLayer = nullptr;
}

std::vector<Object*>& Scene::getMyObjects() {
    return myObjects;
}

int& Scene::getIdScene() {
    return idScene;
}

void Scene::addObjectInScene(Object* obj) {
    addObjectInScene(obj,0);
}

void Scene::addObjectInScene(Object* obj, int layer) {
    myObjects.push_back(obj);
    myLayer->addInLayer(obj, layer);
}

void Scene::update(float& deltaTime) {
    if (!myObjects.empty()) {
        for (auto& object : myObjects) {
            object->update(deltaTime);
        }
    }
}

void Scene::render() {
    if (myLayer != nullptr) {
        myLayer->render();
    }
}
