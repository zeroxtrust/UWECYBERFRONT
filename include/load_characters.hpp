#pragma once
#include <string>
#include <vector>
#include "game_state.hpp"

std::vector<Character> loadCharactersFromFile(const std::string& path);
void loadCharacters(const std::string& path);