#pragma once
#include "../Component.h"

class HoverComponent final : public Component {
private:
    sf::RectangleShape* rect;
    
    sf::Texture* myTexture;
    std::string path;
    sf::Color color;
    
    sf::Color outlineColor;
    int outLineTickness;
    
    bool isActive;
    
public:
    HoverComponent(Object* _owner, sf::Color _color);
    HoverComponent(Object* _owner, std::string _path);
    HoverComponent(Object* _owner, int _outlineTicknes, sf::Color _color);
    virtual ~HoverComponent() override;
    
    void setTexture(sf::Texture* newTexture);
    void setColor(sf::Color newColor);
    void setOutlineTickness(int _newOutlineTicknes);
    void setOutlineColor(sf::Color _newOutlineColor);
    
    sf::Texture* getTexture();
    sf::Color& getColor();
    
    int getOutlineTickness();
    sf::Color& getOutlineColor();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
