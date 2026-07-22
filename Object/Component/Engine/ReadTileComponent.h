#pragma once
#include <iostream>

#include "../Component.h"

class ReadTileComponent final : public Component{
private:
    
    Object* addImage;
    Object* removeImage;
    
    std::vector<Object*> myTiles;
    std::string path;
    
    int offsetImage;
    
    sf::RectangleShape* currentSelected;
    Object* tileSelected;
    bool tileSelect;
    
    int currentLigne;
    int currentColonne;
    int nbrColonne;
    
    float X;
    float Y;
    
    sf::Vector2f sizeImage;
    
    int layerSelected;
    
public:
    ReadTileComponent(Object* _owner, std::string _path, int _nbrColonne);
    virtual ~ReadTileComponent() override;
    
    void tileDisplay();
    void addTileFromFile(const std::filesystem::path& _path);
    void removeDisplay();
    
    std::string& getPath();
    Object* getTileSelected();
    int getLayerSelected();
    Object* getRemove();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
