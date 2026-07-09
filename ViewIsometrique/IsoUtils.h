#pragma once
#include "SFML/Graphics.hpp"

class IsoUtils {
private:
    static IsoUtils* myInstance;
    
    sf::Vector2f tileSize;
    sf::Vector2f origin;
    
    IsoUtils();
    
public:
    ~IsoUtils() = default;
    
    static IsoUtils* getInstance();
    
    void setTileSize(sf::Vector2f _tileSize);
    void setOrigin(sf::Vector2f _origin);
    
    sf::Vector2f gridToScreen(sf::Vector2i gridSize);
    sf::Vector2f screenToGrid(sf::Vector2f screenSize);
    
};
