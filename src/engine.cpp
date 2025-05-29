#include "engine.hpp"
#include "game_state.hpp"
#include "ui.hpp"
#include "mission_logic.hpp"
#include <iostream>

Engine::Engine(GameStateManager* gs) : game_state(gs), running(true) {
    // Create window with more specific settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    
    window.create(sf::VideoMode(1200, 800), "CYBERFRONT: Digital Siege", 
                  sf::Style::Close | sf::Style::Titlebar, settings);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    
    ui = std::make_unique<UI>(game_state, &window);
    mission_logic = std::make_unique<MissionLogic>(game_state);
    
    std::cout << "[ENGINE] Window created: " << window.getSize().x << "x" << window.getSize().y << std::endl;
    std::cout << "[ENGINE] Initialized successfully" << std::endl;
}

Engine::~Engine() {
    shutdown();
}

void Engine::run() {
    std::cout << "[ENGINE] Starting main game loop" << std::endl;
    std::cout << "[ENGINE] Press 1 to start campaign, ESC to exit" << std::endl;
    
    sf::Clock clock;
    int frame_count = 0;
    
    while (running && window.isOpen()) {
        float delta_time = delta_clock.restart().asSeconds();
        
        // Debug: Print frame info every 60 frames (about once per second)
        frame_count++;
        if (frame_count % 60 == 0) {
            std::cout << "[ENGINE] Frame " << frame_count << " - State: " << static_cast<int>(game_state->getState()) << std::endl;
        }
        
        handleEvents();
        
        if (!running) {
            std::cout << "[ENGINE] Running flag set to false, exiting..." << std::endl;
            break;
        }
        
        if (!window.isOpen()) {
            std::cout << "[ENGINE] Window closed, exiting..." << std::endl;
            break;
        }
        
        update(delta_time);
        render();
        
        // Small sleep to prevent excessive CPU usage
        sf::sleep(sf::milliseconds(1));
    }
    
    std::cout << "[ENGINE] Game loop ended after " << frame_count << " frames" << std::endl;
}

void Engine::handleEvents() {
    sf::Event event;
    bool event_processed = false;
    
    while (window.pollEvent(event)) {
        event_processed = true;
        
        // Debug: Print all events
        std::cout << "[EVENT] Type: " << event.type;
        if (event.type == sf::Event::KeyPressed) {
            std::cout << " Key: " << event.key.code;
        }
        std::cout << std::endl;
        
        if (event.type == sf::Event::Closed) {
            std::cout << "[EVENT] Window close requested" << std::endl;
            running = false;
            window.close();
            return;
        }
        
        if (event.type == sf::Event::LostFocus) {
            std::cout << "[EVENT] Window lost focus" << std::endl;
            continue; // Don't exit on focus loss
        }
        
        if (event.type == sf::Event::GainedFocus) {
            std::cout << "[EVENT] Window gained focus" << std::endl;
            continue;
        }
        
        if (event.type == sf::Event::KeyPressed) {
            std::cout << "[INPUT] Key pressed: " << event.key.code << " in state " << static_cast<int>(game_state->getState()) << std::endl;
            
            // Global ESC handler
            if (event.key.code == sf::Keyboard::Escape) {
                if (game_state->getState() == GameState::MAIN_MENU) {
                    std::cout << "[INPUT] ESC in main menu - exiting game" << std::endl;
                    running = false;
                    return;
                } else {
                    std::cout << "[INPUT] ESC - returning to main menu" << std::endl;
                    game_state->setState(GameState::MAIN_MENU);
                    continue;
                }
            }
            
            // State-specific handlers
            if (game_state->getState() == GameState::MAIN_MENU) {
                if (event.key.code == sf::Keyboard::Num1) {
                    std::cout << "[INPUT] Starting campaign..." << std::endl;
                    game_state->setState(GameState::MISSION_SELECT);
                }
            }
            else if (game_state->getState() == GameState::MISSION_SELECT) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num5) {
                    int mission_index = event.key.code - sf::Keyboard::Num1;
                    const auto& missions = game_state->getMissions();
                    if (mission_index < static_cast<int>(missions.size())) {
                        std::cout << "[INPUT] Starting mission " << (mission_index + 1) << ": " << missions[mission_index].title << std::endl;
                        game_state->startMission(missions[mission_index].id);
                        mission_logic->startMission();
                    }
                }
            }
            else if (game_state->getState() == GameState::IN_MISSION) {
                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "[INPUT] SPACE pressed - advancing mission..." << std::endl;
                    
                    Mission* mission = game_state->getCurrentMission();
                    if (mission && mission_logic->isMissionActive()) {
                        // Progress the current mission
                        mission_logic->completeObjective(mission_logic->getCurrentObjective());
                        
                        // Check if mission should complete
                        bool mission_complete = false;
                        if (mission->id == "mission_001") {
                            mission_complete = mission_logic->executeMission001();
                        } else if (mission->id == "mission_002") {
                            mission_complete = mission_logic->executeMission002();
                        } else if (mission->id == "mission_003") {
                            mission_complete = mission_logic->executeMission003();
                        } else if (mission->id == "mission_004") {
                            mission_complete = mission_logic->executeMission004();
                        } else if (mission->id == "mission_final") {
                            mission_complete = mission_logic->executeMissionFinal();
                            if (mission_complete) {
                                game_state->setState(GameState::VICTORY);
                                continue;
                            }
                        }
                        
                        if (mission_complete) {
                            game_state->completeMission(true);
                        }
                    }
                }
            }
            else if (game_state->getState() == GameState::DEBRIEF) {
                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "[INPUT] Continuing to mission select..." << std::endl;
                    game_state->setState(GameState::MISSION_SELECT);
                }
            }
            else if (game_state->getState() == GameState::VICTORY) {
                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "[INPUT] Victory - returning to main menu..." << std::endl;
                    game_state->setState(GameState::MAIN_MENU);
                }
            }
        }
        
        // Pass event to UI
        ui->handleEvent(event);
    }
    
    // Debug: Print if no events were processed
    static int no_event_count = 0;
    if (!event_processed) {
        no_event_count++;
        if (no_event_count % 300 == 0) { // Print every 5 seconds at 60fps
            std::cout << "[ENGINE] No events for " << no_event_count << " frames" << std::endl;
        }
    } else {
        no_event_count = 0;
    }
}

void Engine::update(float delta_time) {
    if (game_state->getState() == GameState::IN_MISSION) {
        mission_logic->updateMission(delta_time);
    }
    
    ui->update(delta_time);
}

void Engine::render() {
    if (!window.isOpen()) {
        return;
    }
    
    // Clear with dark blue background
    window.clear(sf::Color(20, 25, 40));
    
    // Render UI
    ui->render();
    
    // Display
    window.display();
}

void Engine::shutdown() {
    std::cout << "[ENGINE] Shutting down..." << std::endl;
    if (window.isOpen()) {
        window.close();
    }
    std::cout << "[ENGINE] Shutdown complete" << std::endl;
}


