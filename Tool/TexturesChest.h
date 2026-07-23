#pragma once
#include <vector>
#include <algorithm>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

class TexturesChest  {
private:
	static TexturesChest* myInstance;
	std::string error;

	std::unordered_map<std::string, sf::Texture*> myTextures;
	std::unordered_map<std::string, sf::Font*> myFonts;
	
	TexturesChest();
	
public:
    ~TexturesChest();
	
	static TexturesChest* getInstance();
	
	sf::Texture* getTextureFromPath(std::string name);
	sf::Texture* getTextureFromTexture(sf::Texture* texture);
	sf::Font* getFont(std::string name);
	
	void deleteSingleton();
};
