#pragma once
#include "../Component.h"

class ReadTile final : public Component{
private:
    
    Object* addImage;
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
    
    sf::Vector2f _sizeImage;
    
public:
    ReadTile(Object* _owner, std::string _path, int _nbrColonne);
    virtual ~ReadTile() override;
    
    void tileDisplay();
    void addTileFromFile(const std::filesystem::path& _path);
    
    std::string& getPath();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
