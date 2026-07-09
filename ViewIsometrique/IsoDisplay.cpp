#include "IsoDisplay.h"

#include "../Object/Object.h"
#include "IsoComponent.h"
#include "../Scene/Scene.h"

IsoDisplay::IsoDisplay(Object* _owner) : Component(_owner), scene(owner->getCurrentScene()){
}

bool IsoDisplay::compareDepth(Object* a, Object* b) {
    IsoComponent* isoA = a->getComponent<IsoComponent>();
    IsoComponent* isoB = b->getComponent<IsoComponent>();
    
    int depthA;
    if (isoA != nullptr) {
        depthA = isoA->getDepth();
    } else {
        depthA = (int)a->getPosition().y;
    }

    int depthB;
    if (isoB != nullptr) {
        depthB = isoB->getDepth();
    } else {
        depthB = (int)b->getPosition().y;
    }

    return depthA < depthB;
}

void IsoDisplay::render() {
    Layer* currentLayer = scene->getLayer();
    if (!currentLayer->getVecLayers().empty()) {
        for (auto& layer : currentLayer->getVecLayers()) {
            if (!layer.empty()) {
                std::sort(layer.begin(), layer.end(), compareDepth);
            }
        }
    }
}
