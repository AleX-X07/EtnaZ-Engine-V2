#pragma once
#include "SFML/Graphics.hpp"

#include "../Scene/Scene.h"
#include "../Dev.h"

class GameEngine {
private:
	static sf::RenderWindow* window;
	
	static Scene* currentScene;
	 
	sf::Clock clock;
	float deltaTime;
	
	void updateEvent();
	void updateTime();
	void update(float& deltaTime);
	void render();
	
public:
	GameEngine();
	~GameEngine();
	
	static sf::RenderWindow* getWindow();
	static Scene* getCurrentScene();
	
	void run();
	
	// Temp
	static void setCurrentScene(Scene* scene);
};
