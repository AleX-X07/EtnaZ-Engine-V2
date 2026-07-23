#include "TexturesChest.h"

TexturesChest* TexturesChest::myInstance = nullptr;

TexturesChest::TexturesChest() {
    sf::Texture* tex = new sf::Texture();
    error = "Assets/ErreurChargementImage.png";
    if (tex->loadFromFile(error)) {
        myTextures[error] = tex;
    }
    else {
        delete tex;
        tex = nullptr;
    }
}

TexturesChest::~TexturesChest() {
    for (auto& [k,v] : myTextures) {
        delete v;
        v = nullptr;
    }
    myTextures.clear();
    
    for (auto& [k,v] : myFonts) {
        delete v;
        v = nullptr;
    }
    myFonts.clear();
}

TexturesChest* TexturesChest::getInstance() {
    if (myInstance == nullptr) {
        myInstance = new TexturesChest();
    }
    return myInstance;
}

sf::Texture* TexturesChest::getTextureFromPath(std::string name) {
    auto it = myTextures.find(name);
    if (it != myTextures.end()) {
        return it->second;
    }
    else {
        sf::Texture* texture = new sf::Texture();
        if (texture->loadFromFile(name)) {
            myTextures[name] = texture;
            return texture;
        }
        else {
            auto crash = myTextures.find(error);
            if (crash != myTextures.end()) {
                return crash->second;
            }
            else {
                delete texture;
                texture = nullptr;
                return nullptr;
            }
        }
    }
}

sf::Texture* TexturesChest::getTextureFromTexture(sf::Texture* texture) {
    for (auto& [k,v] : myTextures) {
        if (v == texture) {
            return v;
        }
    }
    auto crash = myTextures.find(error);
    if (crash != myTextures.end()) {
        return crash->second;
    }
    else {
        return nullptr;   
    }
}

sf::Font* TexturesChest::getFont(std::string name) {
    auto it = myFonts.find(name);
    if (it != myFonts.end()) {
        return it->second;
    }
    else {
        sf::Font* font = new sf::Font(name);
        if (font) {
            myFonts[name] = font;
            return font;
        }
        else {
            delete font;
            font = nullptr;
            return nullptr;
        }
    }
}

void TexturesChest::deleteSingleton() {
    delete myInstance;
    myInstance = nullptr;
}
