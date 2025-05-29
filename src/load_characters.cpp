#include "load_characters.hpp"
#include <iostream>
#include <fstream>

#ifdef __has_include
    #if __has_include(<nlohmann/json.hpp>)
        #include <nlohmann/json.hpp>
        #define HAS_NLOHMANN_JSON
    #elif __has_include("nlohmann/json.hpp")
        #include "nlohmann/json.hpp"
        #define HAS_NLOHMANN_JSON
    #endif
#endif

#ifdef HAS_NLOHMANN_JSON
using json = nlohmann::json;
#endif

std::vector<Character> loadCharactersFromFile(const std::string& path) {
    std::vector<Character> characters;
    
#ifdef HAS_NLOHMANN_JSON
    std::ifstream file(path);
    if (!file) {
        std::cerr << "[ERROR] Couldn't open: " << path << std::endl;
        return characters;
    }

    try {
        json data;
        file >> data;

        for (const auto& char_json : data["characters"]) {
            Character character;
            character.id = char_json["id"];
            character.codename = char_json["codename"];
            character.name = char_json["name"];
            character.role = char_json["role"];
            character.affiliation = char_json["affiliation"];
            character.bio = char_json["bio"];
            
            for (const auto& skill : char_json["skills"]) {
                character.skills.push_back(skill);
            }
            
            characters.push_back(character);
        }
        
        std::cout << "[CHARACTERS] Loaded " << characters.size() << " characters from " << path << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Failed to parse JSON: " << e.what() << std::endl;
    }
#else
    std::cout << "[CHARACTERS] JSON library not available, using hardcoded characters" << std::endl;
    
    Character philono;
    philono.id = "ph01";
    philono.codename = "PHILONO";
    philono.name = "Unknown";
    philono.role = "Player Character / Commander";
    philono.affiliation = "EU Cyber Defense";
    philono.bio = "Silent operator and leader of the PHILONO task force.";
    philono.skills = {"Strategic planning", "Threat coordination", "Diplomacy"};
    characters.push_back(philono);
    
    Character aido;
    aido.id = "ai01";
    aido.codename = "AIDO";
    aido.name = "Dr. Demetri Dobrev";
    aido.role = "Antagonist";
    aido.affiliation = "Former UWE Lecturer / Rogue Russian Cyber Operative";
    aido.bio = "Cybersecurity educator turned traitor. Mastermind behind the Digital Siege.";
    aido.skills = {"Rootkit engineering", "Insider threats", "Supply chain manipulation"};
    characters.push_back(aido);
    
    Character youss;
    youss.id = "yo01";
    youss.codename = "YOUSS";
    youss.name = "Dr. Yousef E";
    youss.role = "AI Strategist / Ally";
    youss.affiliation = "African Cyber Alliance";
    youss.bio = "Founder of Nyota, Africa's first predictive threat detection AI.";
    youss.skills = {"AI defense", "Threat prediction", "Digital sovereignty"};
    characters.push_back(youss);
    
    Character byte_ai;
    byte_ai.id = "by01";
    byte_ai.codename = "BYTE";
    byte_ai.name = "BYTE";
    byte_ai.role = "AI Assistant";
    byte_ai.affiliation = "PHILONO";
    byte_ai.bio = "Embedded AI trained on billions of log entries and threat patterns.";
    byte_ai.skills = {"Forensics", "Log analysis", "Pattern matching"};
    characters.push_back(byte_ai);
    
    Character sage;
    sage.id = "sa01";
    sage.codename = "SAGE";
    sage.name = "Elena Vos";
    sage.role = "Cryptography Expert";
    sage.affiliation = "PHILONO";
    sage.bio = "Ex-military cryptographer who now cracks and builds encryption systems.";
    sage.skills = {"Encryption", "Decryption", "Quantum-safe algorithms"};
    characters.push_back(sage);
    
    Character spinner;
    spinner.id = "sp01";
    spinner.codename = "SPINNER";
    spinner.name = "Jamal Beckett";
    spinner.role = "Social Engineering Analyst";
    spinner.affiliation = "PHILONO";
    spinner.bio = "Psychologist and human behavior hacker.";
    spinner.skills = {"Social engineering", "Phishing detection", "Behavioral analysis"};
    characters.push_back(spinner);
#endif
    
    return characters;
}

void loadCharacters(const std::string& path) {
    auto characters = loadCharactersFromFile(path);
    
    std::cout << "=== Known Characters ===" << std::endl;
    for (const auto& character : characters) {
        std::cout << character.codename << " - " << character.role << "\n";
        std::cout << "   Skills: ";
        for (const auto& skill : character.skills) {
            std::cout << skill << ", ";
        }
        std::cout << "\n\n";
    }
} 