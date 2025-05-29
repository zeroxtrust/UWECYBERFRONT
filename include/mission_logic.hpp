#pragma once
#include "game_state.hpp"
#include "forensic_tools.hpp"
#include <SFML/Graphics.hpp>

class MissionLogic {
private:
    GameStateManager* game_state;
    int current_objective;
    sf::Clock mission_timer;
    bool mission_active;

public:
    MissionLogic(GameStateManager* gs);
    
    void startMission();
    void updateMission(float delta_time);
    bool checkObjectiveComplete(int objective_index);
    void completeObjective(int objective_index);
    void failMission(const std::string& reason);
    
    bool executeMission001();
    bool executeMission002();
    bool executeMission003();
    bool executeMission004();
    bool executeMissionFinal();
    
    bool rootkitScanMinigame();
    bool logDecryptionMinigame();
    bool packetAnalysisMinigame();
    bool malwareReverseMinigame();
    bool honeypotSetupMinigame();
    
    int getCurrentObjective() const { return current_objective; }
    float getMissionTime() const { return mission_timer.getElapsedTime().asSeconds(); }
    bool isMissionActive() const { return mission_active; }
};

struct MinigameResult {
    bool success;
    int score;
    float time_taken;
    std::string details;
};