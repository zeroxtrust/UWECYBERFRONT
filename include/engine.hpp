
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameStateManager;
class UI;
class MissionLogic;

class Engine {
private:
    sf::RenderWindow window;
    GameStateManager* game_state;
    std::unique_ptr<UI> ui;
    std::unique_ptr<MissionLogic> mission_logic;
    sf::Clock delta_clock;
    bool running;

public:
    Engine(GameStateManager* gs);
    ~Engine();
    
    void run();
    void handleEvents();
    void update(float delta_time);
    void render();
    void shutdown();
    
    sf::RenderWindow& getWindow() { return window; }
};