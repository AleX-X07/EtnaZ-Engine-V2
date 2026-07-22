#pragma once
#include <vector>
#include <algorithm>

#include "SFML/Graphics/Texture.hpp"

class TexturesChest  {
private:
	static TexturesChest* myInstance;

	std::pmr::vector<sf::Texture*> myTextures;
	
	TexturesChest() = default;
	
public:
    ~TexturesChest();
	
	static TexturesChest* getInstance();
	
	void addTextures(sf::Texture* texture);
	
	void deleteSingleton();
};
