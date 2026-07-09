#include "IsoUtils.h"

IsoUtils* IsoUtils::myInstance = nullptr;

IsoUtils::IsoUtils() {
    tileSize = sf::Vector2f(0,0);
    origin = sf::Vector2f(0,0);
}

IsoUtils* IsoUtils::getInstance() {
    if (myInstance == nullptr) {
        myInstance = new IsoUtils();
    }
    return myInstance;
}

void IsoUtils::setTileSize(sf::Vector2f _tileSize) {
    tileSize = _tileSize;
}

void IsoUtils::setOrigin(sf::Vector2f _origin) {
    origin = _origin;
}

sf::Vector2f IsoUtils::gridToScreen(sf::Vector2i gridSize) {
    float screenX = (gridSize.x - gridSize.y) * (tileSize.x / 2);
    float screenY = (gridSize.x + gridSize.y) * (tileSize.y / 2);
    return {screenX + origin.x, screenY + origin.y};
}

sf::Vector2f IsoUtils::screenToGrid(sf::Vector2f screenSize) {
    sf::Vector2f adjusted = screenSize - origin;
    
    float gridXf = (adjusted.x / (tileSize.x / 2.f) + adjusted.y / (tileSize.y / 2.f)) / 2.f;
    float gridYf = (adjusted.y / (tileSize.y / 2.f) - adjusted.x / (tileSize.x / 2.f)) / 2.f;
    return sf::Vector2f(std::floor(gridXf), std::floor(gridYf));
}
