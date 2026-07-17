#pragma once
#include "../Component.h"

class ReadTile final : public Component{
private:
    std::vector<Object*> myTiles;
    std::string path;
    
public:
    ReadTile(Object* _owner, std::string _path, int _nbrColonne);
    virtual ~ReadTile() override;
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
