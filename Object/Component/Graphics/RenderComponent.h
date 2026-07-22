#pragma once
#include "../Component.h"

class GameEngine;

class RenderComponent final : public Component{
private:
    sf::RectangleShape* rect;
    
    sf::Texture* texture;
    sf::Color* color;
    
    sf::Color outlineColor;
    int outlineTickness;
    
    bool isActive;

public:
    RenderComponent(Object* _owner, std::string _path);
    RenderComponent(Object* _owner, sf::Texture* _text);
    RenderComponent(Object* _owner, sf::Color _color);  
    RenderComponent(Object* _owner, int _outlineTickness, sf::Color _color);
    virtual ~RenderComponent() override;
    
    void setTexture(sf::Texture* newTexture);
    void setColor(sf::Color newColor);
    
    void setOutline(int _newOutline);
    void setOutlineColor(sf::Color _newColor);
    
    sf::RectangleShape* getRect();
    
    sf::Texture* getTexture();;
    sf::Color* getColor();
    
    void setVisibility(bool newVisibility);
    bool getVisibility();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
