#include "Layer.h"

Layer::Layer() {
    nbrLayers = 1;
    setNbrLayer(1);
}

Layer::~Layer() {
    layers.clear();
}

std::vector<std::vector<Object*>>& Layer::getVecLayers() {
    return layers;
}

void Layer::setNbrLayer(int _nbrLayers) {
    nbrLayers = _nbrLayers;
    for (int X = 0; X < nbrLayers; X++) {
        std::vector<Object*> newLayer;
        layers.push_back(newLayer);
    }
}

void Layer::addInLayer(Object* myObject, int layer) {
    if (layer < nbrLayers ) {
        layers[layer].push_back(myObject);
    }
}

int Layer::getCurrentLayer(Object* myObject) {
    int posInLayer = 0;
    for (int i = 0; i < static_cast<int>(layers.size()); i++) {
        auto it = std::find(layers[i].begin(), layers[i].end(), myObject);
        if (it != layers[i].end()) {
            return i;
        }
    }
    return -1;
}

void Layer::render() {
    if (!layers.empty()) {
        for (auto& layer : layers) {
            if (!layer.empty()) {
                for (auto& object : layer) {
                    object->render();
                }
            }
        }
    }
}
