#pragma once
#include <string>
#include <vector>
#include "game_state.hpp"

std::vector<Mission> loadMissionsFromFile(const std::string& path);
void loadMissions(const std::string& path);