#pragma once
#include "../Component.h"

class ReadTile final : public Component{
private:
    std::vector<Object*> myButtons;
    std::vector<Object*> myTiles;
    std::string path;
    
    int offsetImage;
    
    sf::RectangleShape* currentSelected;
    Object* tileSelected;
    bool tileSelect;
    
public:
    ReadTile(Object* _owner, std::string _path, int _nbrColonne);
    virtual ~ReadTile() override;
    
    void tileDisplay();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
