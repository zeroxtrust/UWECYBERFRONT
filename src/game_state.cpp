#include "game_state.hpp"
#include <algorithm>
#include <iostream>

GameStateManager::GameStateManager() : current_state(GameState::MAIN_MENU), current_mission(nullptr) {
    progress.trust_uk = 50;
    progress.trust_youss = 50;
    progress.trust_eu = 75;
}

void GameStateManager::setState(GameState new_state) {
    current_state = new_state;
    std::cout << "[STATE] Changed to: " << static_cast<int>(new_state) << std::endl;
}

void GameStateManager::loadMissions(const std::vector<Mission>& mission_data) {
    missions = mission_data;
    std::cout << "[GAME] Loaded " << missions.size() << " missions" << std::endl;
}

void GameStateManager::loadCharacters(const std::vector<Character>& character_data) {
    characters = character_data;
    std::cout << "[GAME] Loaded " << characters.size() << " characters" << std::endl;
}

void GameStateManager::startMission(const std::string& mission_id) {
    auto it = std::find_if(missions.begin(), missions.end(),
        [&mission_id](const Mission& m) { return m.id == mission_id; });
    
    if (it != missions.end()) {
        current_mission = &(*it);
        current_mission->state = MissionState::IN_PROGRESS;
        setState(GameState::IN_MISSION);
        std::cout << "[MISSION] Started: " << current_mission->title << std::endl;
    } else {
        std::cout << "[ERROR] Mission not found: " << mission_id << std::endl;
    }
}

void GameStateManager::completeMission(bool success) {
    if (current_mission) {
        current_mission->state = success ? MissionState::COMPLETED_SUCCESS : MissionState::COMPLETED_FAILURE;
        
        if (success) {
            int base_score = 100;
            current_mission->score = base_score;
            addScore(base_score);
            
            if (current_mission->id == "mission_001") {
                adjustTrust("EU", 10);
                setStoryFlag("rootkit_found", true);
            } else if (current_mission->id == "mission_002") {
                adjustTrust("UK", -5);
                setStoryFlag("aido_identified", true);
            } else if (current_mission->id == "mission_003") {
                if (getStoryFlag("youss_contacted")) {
                    progress.youss_alliance = true;
                    adjustTrust("YOUSS", 25);
                }
            }
        } else {
            adjustTrust("EU", -5);
            current_mission->score = 0;
        }
        
        setState(GameState::DEBRIEF);
        std::cout << "[MISSION] Completed: " << (success ? "SUCCESS" : "FAILURE") << std::endl;
    }
}

void GameStateManager::adjustTrust(const std::string& faction, int change) {
    if (faction == "UK") {
        progress.trust_uk = std::max(0, std::min(100, progress.trust_uk + change));
    } else if (faction == "YOUSS") {
        progress.trust_youss = std::max(0, std::min(100, progress.trust_youss + change));
    } else if (faction == "EU") {
        progress.trust_eu = std::max(0, std::min(100, progress.trust_eu + change));
    }
    
    std::cout << "[TRUST] " << faction << " adjusted by " << change 
              << " (UK:" << progress.trust_uk 
              << " YOUSS:" << progress.trust_youss 
              << " EU:" << progress.trust_eu << ")" << std::endl;
}

void GameStateManager::setStoryFlag(const std::string& flag, bool value) {
    progress.story_flags[flag] = value;
    std::cout << "[FLAG] " << flag << " = " << (value ? "true" : "false") << std::endl;
}

bool GameStateManager::getStoryFlag(const std::string& flag) const {
    auto it = progress.story_flags.find(flag);
    return (it != progress.story_flags.end()) ? it->second : false;
}

Character* GameStateManager::getCharacter(const std::string& id) {
    auto it = std::find_if(characters.begin(), characters.end(),
        [&id](const Character& c) { return c.id == id; });
    return (it != characters.end()) ? &(*it) : nullptr;
} 