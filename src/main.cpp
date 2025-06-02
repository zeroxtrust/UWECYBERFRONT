#include <iostream>
#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "game_state.hpp"
#include "mission_logic.hpp"
#include "ui.hpp"
#include "load_missions.hpp"
#include "load_characters.hpp"

int main() {
    std::cout << R"(
 ██╗   ██╗██╗    ██╗███████╗     ██████╗██╗   ██╗██████╗ ███████╗██████╗ ███████╗██████╗  ██████╗ ███╗   ██╗████████╗
██║   ██║██║    ██║██╔════╝    ██╔════╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔══██╗██╔════╝██╔══██╗██╔═══██╗████╗  ██║╚══██╔══╝
██║   ██║██║ █╗ ██║█████╗      ██║      ╚████╔╝ ██████╔╝█████╗  ██████╔╝█████╗  ██████╔╝██║   ██║██╔██╗ ██║   ██║   
██║   ██║██║███╗██║██╔══╝      ██║       ╚██╔╝  ██╔══██╗██╔══╝  ██╔══██╗██╔══╝  ██╔══██╗██║   ██║██║╚██╗██║   ██║   
╚██████╔╝╚███╔███╔╝███████╗    ╚██████╗   ██║   ██████╔╝███████╗██║  ██║██║     ██║  ██║╚██████╔╝██║ ╚████║   ██║   
 ╚═════╝  ╚══╝╚══╝ ╚══════╝     ╚═════╝   ╚═╝   ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   
                                                                                                                                                                                                        
                          DIGITAL SIEGE
                      The Insider War - 2032
)" << std::endl;

    std::cout << "Initializing CYBERFRONT: Digital Siege..." << std::endl;
    
    GameStateManager gameState;
    Engine engine(&gameState);
    
    std::vector<Mission> missions = loadMissionsFromFile("data/missions.json");
    std::vector<Character> characters = loadCharactersFromFile("data/characters.json");
    
    gameState.loadMissions(missions);
    gameState.loadCharacters(characters);
    
    std::cout << "\n=== GAME INITIALIZED ===" << std::endl;
    std::cout << "Missions loaded: " << missions.size() << std::endl;
    std::cout << "Characters loaded: " << characters.size() << std::endl;
    std::cout << "========================\n" << std::endl;
    std::cout << " CONTROLS:" << std::endl;
    std::cout << "   Press 1 - Start Campaign" << std::endl;
    std::cout << "   Press ESC - Exit" << std::endl;
    std::cout << "========================\n" << std::endl;
    
    engine.run();
    
    return 0;
}
