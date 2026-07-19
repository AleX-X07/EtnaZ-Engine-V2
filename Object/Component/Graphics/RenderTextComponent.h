#pragma once
#include "../Component.h"

class RenderTextComponent final : public Component {
private:
    std::string path;
    
    sf::Text* myText;
    sf::Font* myFont;
    
    bool isActive;
    
public:
    RenderTextComponent(Object* _owner, std::string _path);
    RenderTextComponent(Object* _owner, std::string _path, int _characterSize);
    RenderTextComponent(Object* _owner, std::string _path, int _characterSize, sf::Color _color);
    virtual ~RenderTextComponent() override;
    
    void setText(std::string _text);
    
    void setVisibility(bool _visible);
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
