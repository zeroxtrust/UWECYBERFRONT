#pragma once
#include <string>
#include <vector>
#include <map>

enum class GameState {
    MAIN_MENU,
    MISSION_SELECT,
    IN_MISSION,
    FORENSICS_LAB,
    BRIEFING,
    DEBRIEF,
    GAME_OVER,
    VICTORY
};

enum class MissionState {
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED_SUCCESS,
    COMPLETED_FAILURE
};

struct Mission {
    std::string id;
    std::string title;
    std::string location;
    std::string briefing;
    std::vector<std::string> objectives;
    std::string success_criteria;
    std::string failure_criteria;
    std::string next;
    MissionState state = MissionState::NOT_STARTED;
    int score = 0;
};

struct Character {
    std::string id;
    std::string codename;
    std::string name;
    std::string role;
    std::string affiliation;
    std::string bio;
    std::vector<std::string> skills;
};

struct GameProgress {
    int current_mission_index = 0;
    int total_score = 0;
    int trust_uk = 50;
    int trust_youss = 50;
    int trust_eu = 75;
    bool youss_alliance = false;
    bool transparency_route = false;
    std::vector<std::string> completed_objectives;
    std::map<std::string, bool> story_flags;
};

class GameStateManager {
private:
    GameState current_state;
    std::vector<Mission> missions;
    std::vector<Character> characters;
    GameProgress progress;
    Mission* current_mission;

public:
    GameStateManager();
    
    void setState(GameState new_state);
    GameState getState() const { return current_state; }
    
    void loadMissions(const std::vector<Mission>& mission_data);
    void loadCharacters(const std::vector<Character>& character_data);
    Mission* getCurrentMission() { return current_mission; }
    void startMission(const std::string& mission_id);
    void completeMission(bool success);
    
    GameProgress& getProgress() { return progress; }
    void addScore(int points) { progress.total_score += points; }
    void adjustTrust(const std::string& faction, int change);
    
    void setStoryFlag(const std::string& flag, bool value);
    bool getStoryFlag(const std::string& flag) const;
    
    const std::vector<Mission>& getMissions() const { return missions; }
    const std::vector<Character>& getCharacters() const { return characters; }
    Character* getCharacter(const std::string& id);
}; 