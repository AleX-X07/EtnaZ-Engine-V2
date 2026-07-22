#include "GameEngine.h"

sf::RenderWindow* GameEngine::window = nullptr;
Scene* GameEngine::currentScene = nullptr;


GameEngine::GameEngine() {
    
    Input::getInstance();
    TexturesChest::getInstance();
    
    window = new sf::RenderWindow(sf::VideoMode({1280,720}),"EtnaZ-Engine");
    deltaTime = 0.0f;
    
    // Temp
    Dev dev;
}

GameEngine::~GameEngine() {
    delete currentScene;
    currentScene = nullptr;
    
    delete window;
    window = nullptr;
    
    Input::getInstance()->deleteSingleton();
    TexturesChest::getInstance()->deleteSingleton();
}


void GameEngine::updateEvent() {
    Input::getInstance()->reset();
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        Input::getInstance()->setEvent(*event);
    }
}

void GameEngine::updateTime() {
    sf::Time elapsed = clock.getElapsedTime();
    clock.restart();
    deltaTime = elapsed.asSeconds();
}

void GameEngine::update(float& deltaTime) {
    if (currentScene != nullptr) {
        currentScene->update(deltaTime);
    }
}

void GameEngine::render() {
    if (currentScene != nullptr) {
        currentScene->render();
    }
}


sf::RenderWindow* GameEngine::getWindow() {
    return window;
}

Scene* GameEngine::getCurrentScene() {
    return currentScene;
}


void GameEngine::run() {
    while (window->isOpen()) {
        updateTime();
        updateEvent();
        update(deltaTime);
        window->clear();
        render();
        window->display();
    }
}


// Temp
void GameEngine::setCurrentScene(Scene* scene) {
    currentScene = scene;
}
