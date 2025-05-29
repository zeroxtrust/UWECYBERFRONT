#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "CYBERFRONT Working Test");
    
    // Try to load a system font
    sf::Font font;
    bool font_loaded = false;
    
    // Try multiple font paths
    std::vector<std::string> font_paths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/System/Library/Fonts/Arial.ttf",
        "/usr/share/fonts/TTF/arial.ttf"
    };
    
    for (const auto& path : font_paths) {
        if (font.loadFromFile(path)) {
            font_loaded = true;
            std::cout << "✅ Font loaded from: " << path << std::endl;
            break;
        }
    }
    
    if (!font_loaded) {
        std::cout << "❌ No fonts found, using default" << std::endl;
    }
    
    // Create text
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("CYBERFRONT: DIGITAL SIEGE");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Green);
    title.setPosition(200, 200);
    
    sf::Text menu;
    if (font_loaded) {
        menu.setFont(font);
    }
    menu.setString("1. START CAMPAIGN");
    menu.setCharacterSize(28);
    menu.setFillColor(sf::Color::White);
    menu.setPosition(450, 350);
    
    sf::Text instruction;
    if (font_loaded) {
        instruction.setFont(font);
    }
    instruction.setString("ESC. EXIT");
    instruction.setCharacterSize(24);
    instruction.setFillColor(sf::Color::Yellow);
    instruction.setPosition(480, 400);
    
    std::cout << "🎮 Look for green text in the window!" << std::endl;
    std::cout << "If you see text, we can fix the main game!" << std::endl;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed: " << event.key.code << std::endl;
            }
        }
        
        window.clear(sf::Color(20, 25, 40));
        window.draw(title);
        window.draw(menu);
        window.draw(instruction);
        window.display();
    }
    
    return 0;
}
