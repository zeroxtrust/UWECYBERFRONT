#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Text Test");
    
    sf::Text title;
    title.setString("CYBERFRONT: DIGITAL SIEGE");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Green);
    title.setPosition(300, 200);
    
    sf::Text menu;
    menu.setString("1. START CAMPAIGN");
    menu.setCharacterSize(24);
    menu.setFillColor(sf::Color::White);
    menu.setPosition(450, 350);
    
    std::cout << "If you see green text, SFML text rendering works!" << std::endl;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }
        
        window.clear(sf::Color(20, 25, 40));
        window.draw(title);
        window.draw(menu);
        window.display();
    }
    
    return 0;
}
