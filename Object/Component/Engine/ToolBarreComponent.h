#pragma once
#include "../Component.h"

class Scene;

struct argsButton {
    std::string text;
    sf::Vector2f size;
};

class ToolBarreComponent final : public Component {
private:
    std::vector<Object*> myObjects;
    
public:
    ToolBarreComponent(Object* _owner);
    virtual ~ToolBarreComponent() override;
    
    sf::Vector2f getPosLastObj();
    
    Object* createButton(Scene* scene, sf::Vector2f size, std::string _font, std::string _text, int sizeText,  
        sf::Color colorText, sf::Color colorhover, std::vector<Component*> persoComp, std::unordered_map<std::string, sf::Vector2f> persoArgs);
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
