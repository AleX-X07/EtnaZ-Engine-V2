#pragma once
#include "SFML/Graphics.hpp"

const sf::Vector2f screen = {1280,720};
const sf::Vector2f level = {screen.x*4,screen.y*4};

const sf::Vector2f toolBarreSize = {screen.x,15};
const sf::Vector2f toolBarrePos = {0,0};

const sf::Vector2f editorWindowSize = {screen.x/4*3,screen.y-toolBarreSize.y};
const sf::Vector2f editorWindowPos = {screen.x/4,toolBarreSize.y};

const sf::Vector2f readerWindowSize = {screen.x/4, screen.y};
const sf::Vector2f readerWindowPos = {0, toolBarreSize.y};


