#include "TexturesChest.h"

TexturesChest* TexturesChest::myInstance = nullptr;

TexturesChest::~TexturesChest() {
    for (auto& t : myTextures) {
        delete t;
        t = nullptr;
    }
    myTextures.clear();
}

TexturesChest* TexturesChest::getInstance() {
    if (myInstance == nullptr) {
        myInstance = new TexturesChest();
    }
    return myInstance;
}

void TexturesChest::addTextures(sf::Texture* texture) {
    if (std::find(myTextures.begin(), myTextures.end(), texture) == myTextures.end()) {
        myTextures.push_back(texture);
    }
}

void TexturesChest::deleteSingleton() {
    delete myInstance;
    myInstance = nullptr;
}
