#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameStateManager;

class UI {
private:
    GameStateManager* game_state;
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text title_text;
    sf::Text menu_text;
    sf::Text status_text;
    sf::RectangleShape background_panel;
    
    sf::Color primary_color;
    sf::Color secondary_color;
    sf::Color accent_color;
    
    bool font_loaded;

public:
    UI(GameStateManager* gs, sf::RenderWindow* win);
    
    void handleEvent(const sf::Event& event);
    void update(float delta_time);
    void render();
    
    void renderMainMenu();
    void renderMissionSelect();
    void renderMissionBriefing();
    void renderInMission();
    void renderForensicsLab();
    void renderDebrief();
    void renderGameOver();
    void renderVictory();
    
    void renderTrustMeters();
    void renderMissionProgress();
    void renderCharacterInfo();
    void renderTerminalEffect(const std::string& text, float x, float y);
    
private:
    void setupFonts();
    void setupColors();
    sf::Text createText(const std::string& content, float x, float y, int size = 24);
}; 