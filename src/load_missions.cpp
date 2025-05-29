#include "load_missions.hpp"
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

std::vector<Mission> loadMissionsFromFile(const std::string& path) {
    std::vector<Mission> missions;
    
#ifdef HAS_NLOHMANN_JSON
    std::ifstream file(path);
    if (!file) {
        std::cerr << "[ERROR] Couldn't open: " << path << std::endl;
        return missions;
    }

    try {
        json data;
        file >> data;

        for (const auto& mission_json : data["missions"]) {
            Mission mission;
            mission.id = mission_json["id"];
            mission.title = mission_json["title"];
            mission.location = mission_json["location"];
            mission.briefing = mission_json["briefing"];
            mission.success_criteria = mission_json["success_criteria"];
            mission.failure_criteria = mission_json["failure_criteria"];
            
            if (mission_json.contains("next") && !mission_json["next"].is_null()) {
                mission.next = mission_json["next"];
            }
            
            for (const auto& obj : mission_json["objectives"]) {
                mission.objectives.push_back(obj);
            }
            
            missions.push_back(mission);
        }
        
        std::cout << "[MISSIONS] Loaded " << missions.size() << " missions from " << path << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Failed to parse JSON: " << e.what() << std::endl;
    }
#else
    std::cout << "[MISSIONS] JSON library not available, using hardcoded missions" << std::endl;
    
    Mission m1;
    m1.id = "mission_001";
    m1.title = "Academic Breach";
    m1.location = "UWE (University of the West of England)";
    m1.briefing = "Strange network activity detected within UWE's cybersecurity department.";
    m1.objectives = {
        "Analyse packet captures from training VM network",
        "Identify rootkit signatures in virtual machines",
        "Decrypt staff communication logs",
        "Trace communication to foreign IP domains"
    };
    m1.success_criteria = "Rootkit signature found, decrypted logs analyzed, source IP traced";
    m1.failure_criteria = "Failure to detect malware or incomplete analysis";
    m1.next = "mission_002";
    missions.push_back(m1);
    
    Mission m2;
    m2.id = "mission_002";
    m2.title = "Code of Deceit";
    m2.location = "CyberFirst Competition Archive";
    m2.briefing = "Malware sample found hidden in popular student repo.";
    m2.objectives = {
        "Reverse engineer the malware sample",
        "Find embedded metadata",
        "Link origin to academic contributor"
    };
    m2.success_criteria = "Metadata reveals author signature and links to AIDO";
    m2.failure_criteria = "Malware not fully reversed or metadata inconclusive";
    m2.next = "mission_003";
    missions.push_back(m2);
    
    Mission m3;
    m3.id = "mission_003";
    m3.title = "University VPN Breach";
    m3.location = "UK Academic Network";
    m3.briefing = "Spoofed UWE emails triggered credential theft at multiple universities.";
    m3.objectives = {
        "Set up honeypots across three university VPNs",
        "Monitor credential misuse",
        "Block external command & control domains"
    };
    m3.success_criteria = "Phishing route blocked, credentials protected";
    m3.failure_criteria = "At least one university system fully compromised";
    m3.next = "mission_004";
    missions.push_back(m3);
    
    Mission m4;
    m4.id = "mission_004";
    m4.title = "The Faculty Firewall";
    m4.location = "National Cyber Security Centre (NCSC)";
    m4.briefing = "Evidence implicates UWE in the breach. Time for a difficult decision.";
    m4.objectives = {
        "Present the forensics case to NCSC",
        "Choose whether to expose or suppress details",
        "Evaluate diplomatic and strategic consequences"
    };
    m4.success_criteria = "Crisis managed with controlled fallout";
    m4.failure_criteria = "Loss of ally trust or intelligence blackout";
    m4.next = "mission_final";
    missions.push_back(m4);
    
    Mission m5;
    m5.id = "mission_final";
    m5.title = "Siege of CyberCity";
    m5.location = "CyberCity HQ";
    m5.briefing = "AIDO launches final cyber siege on Europe's smart city.";
    m5.objectives = {
        "Simultaneously defend Power Grid, Hospital and Airport nodes",
        "Use Nyota AI (YOUSS) for predictive threat defense",
        "Locate AIDO's real control server and disable it"
    };
    m5.success_criteria = "All three sectors survive and AIDO is neutralized";
    m5.failure_criteria = "Any two sectors fall or AIDO escapes undetected";
    missions.push_back(m5);
#endif
    
    return missions;
}

void loadMissions(const std::string& path) {
    auto missions = loadMissionsFromFile(path);
    
    std::cout << "=== Available Missions ===" << std::endl;
    for (const auto& mission : missions) {
        std::cout << "-> " << mission.title << " (" << mission.location << ")\n";
        std::cout << "   Briefing: " << mission.briefing << "\n\n";
    }
} 