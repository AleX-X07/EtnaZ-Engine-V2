#pragma once
#include "../Component.h"

class GameEngine;

class RenderComponent final : public Component{
private:
    sf::Texture* texture;
    sf::RectangleShape* rect;
    sf::Color* color;
    
    bool isActive;

public:
    RenderComponent(Object* _owner, std::string _path);
    RenderComponent(Object* _owner, sf::Color _color);  
    virtual ~RenderComponent() override;
    
    void setTexture(sf::Texture* newTexture);
    void setColor(sf::Color newColor);
    
    sf::RectangleShape* getRect();
    sf::Texture* getTexture();;
    sf::Color* getColor();
    
    void setVisibility(bool newVisibility);
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
