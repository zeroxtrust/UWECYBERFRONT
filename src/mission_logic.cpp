#include "mission_logic.hpp"
#include <iostream>

MissionLogic::MissionLogic(GameStateManager* gs) 
    : game_state(gs), current_objective(0), mission_active(false) {}

void MissionLogic::startMission() {
    mission_active = true;
    current_objective = 0;
    mission_timer.restart();
    
    Mission* mission = game_state->getCurrentMission();
    if (!mission) return;
    
    std::cout << "\n=== MISSION BRIEFING ===" << std::endl;
    std::cout << "Title: " << mission->title << std::endl;
    std::cout << "Location: " << mission->location << std::endl;
    std::cout << "Briefing: " << mission->briefing << std::endl;
    std::cout << "\nObjectives:" << std::endl;
    for (size_t i = 0; i < mission->objectives.size(); ++i) {
        std::cout << (i + 1) << ". " << mission->objectives[i] << std::endl;
    }
    std::cout << "========================" << std::endl;
    std::cout << " Press SPACE to start first objective!" << std::endl;
    std::cout << "========================\n" << std::endl;
    
    // Start with first objective
    if (mission->id == "mission_001") {
        std::cout << " Ready to start: Analyzing packet captures..." << std::endl;
        std::cout << "Press SPACE when ready!" << std::endl;
    }
}

void MissionLogic::updateMission(float /*delta_time*/) {
    // Mission logic now controlled by SPACE key presses only
}

bool MissionLogic::executeMission001() {
    std::cout << "\n--- MISSION 001: Academic Breach ---" << std::endl;
    
    if (current_objective == 0) {
        std::cout << " Executing: Packet Analysis..." << std::endl;
        std::cout << " Scanning training VM network traffic..." << std::endl;
        std::cout << " Suspicious patterns detected!" << std::endl;
        std::cout << "Next: Press SPACE for Objective 2" << std::endl;
        return false; // Don't complete mission yet
    }
    else if (current_objective == 1) {
        std::cout << " Executing: Rootkit Scanner..." << std::endl;
        std::cout << " Scanning system files for malware signatures..." << std::endl;
        std::cout << " AIDO rootkit signature found!" << std::endl;
        game_state->setStoryFlag("rootkit_found", true);
        std::cout << "Next: Press SPACE for Objective 3" << std::endl;
        return false;
    }
    else if (current_objective == 2) {
        std::cout << " Executing: Log Decryption..." << std::endl;
        std::cout << " Breaking encryption on staff communications..." << std::endl;
        std::cout << " Logs decrypted! Russian domain communications found!" << std::endl;
        std::cout << "Next: Press SPACE for Final Objective" << std::endl;
        return false;
    }
    else if (current_objective == 3) {
        std::cout << " Executing: IP Trace..." << std::endl;
        std::cout << " Tracing foreign communications..." << std::endl;
        std::cout << " IP trace complete! Moscow servers identified!" << std::endl;
        std::cout << "\n MISSION COMPLETE: UWE insider threat confirmed!" << std::endl;
        return true; // Mission complete
    }
    
    return false;
}

bool MissionLogic::executeMission002() {
    std::cout << "\n--- MISSION 002: Code of Deceit ---" << std::endl;
    
    if (current_objective == 0) {
        std::cout << " Executing: Malware Reverse Engineering..." << std::endl;
        std::cout << " Disassembling code structure..." << std::endl;
        std::cout << " Malware components identified!" << std::endl;
        std::cout << "Next: Press SPACE for Objective 2" << std::endl;
        return false;
    }
    else if (current_objective == 1) {
        std::cout << " Executing: Metadata Extraction..." << std::endl;
        std::cout << " Scanning for hidden author data..." << std::endl;
        std::cout << " Author signature found: 'DD_2032_UWE'" << std::endl;
        std::cout << "Next: Press SPACE for Final Objective" << std::endl;
        return false;
    }
    else if (current_objective == 2) {
        std::cout << " Executing: Database Cross-Reference..." << std::endl;
        std::cout << " Matching signature to known contributors..." << std::endl;
        std::cout << " Match found: Dr. Demetri Dobrev (AIDO)!" << std::endl;
        game_state->setStoryFlag("aido_identified", true);
        std::cout << "\n BREAKTHROUGH: AIDO's identity confirmed!" << std::endl;
        return true;
    }
    
    return false;
}

bool MissionLogic::executeMission003() {
    std::cout << "\n--- MISSION 003: University VPN Breach ---" << std::endl;
    
    if (current_objective == 0) {
        std::cout << " Executing: Honeypot Deployment..." << std::endl;
        std::cout << " Setting traps across university networks..." << std::endl;
        std::cout << " Honeypots active across 3 universities!" << std::endl;
        std::cout << "Next: Press SPACE for Objective 2" << std::endl;
        return false;
    }
    else if (current_objective == 1) {
        std::cout << " Executing: Credential Monitoring..." << std::endl;
        std::cout << " Watching for theft attempts..." << std::endl;
        std::cout << " Multiple credential theft attempts detected!" << std::endl;
        std::cout << "Next: Press SPACE for Objective 3" << std::endl;
        return false;
    }
    else if (current_objective == 2) {
        std::cout << " Executing: Domain Blocking..." << std::endl;
        std::cout << " Blocking malicious command & control servers..." << std::endl;
        std::cout << " 15 malicious domains blocked!" << std::endl;
        std::cout << "\n Incoming secure call from Dr. Yousef E (YOUSS)..." << std::endl;
        std::cout << "YOUSS: 'PHILONO, we've been tracking similar patterns.'" << std::endl;
        std::cout << "YOUSS: 'Our Nyota AI detected the same signatures. Alliance?'" << std::endl;
        game_state->setStoryFlag("youss_contacted", true);
        game_state->adjustTrust("YOUSS", 25);
        std::cout << "\n YOUSS alliance established!" << std::endl;
        return true;
    }
    
    return false;
}

bool MissionLogic::executeMission004() {
    std::cout << "\n--- MISSION 004: The Faculty Firewall ---" << std::endl;
    
    if (current_objective == 0) {
        std::cout << " At NCSC Headquarters, London" << std::endl;
        std::cout << " Presenting forensics case to NCSC leadership..." << std::endl;
        std::cout << " Evidence presented successfully!" << std::endl;
        std::cout << "Next: Press SPACE for Critical Decision" << std::endl;
        return false;
    }
    else if (current_objective == 1) {
        std::cout << "\n CRITICAL DECISION POINT:" << std::endl;
        std::cout << "1. TRANSPARENCY: Expose UWE publicly" << std::endl;
        std::cout << "2. COVER-UP: Protect UK reputation" << std::endl;
        std::cout << "3. HYBRID: Blame individual, not institution" << std::endl;
        std::cout << " Choosing HYBRID approach..." << std::endl;
        std::cout << "Next: Press SPACE to Execute Decision" << std::endl;
        return false;
    }
    else if (current_objective == 2) {
        std::cout << " Executing: HYBRID Route..." << std::endl;
        std::cout << " Exposing AIDO while protecting UWE..." << std::endl;
        std::cout << " Crisis managed with controlled fallout!" << std::endl;
        game_state->setStoryFlag("hybrid_route", true);
        game_state->adjustTrust("UK", 5);
        game_state->adjustTrust("EU", 10);
        std::cout << "AIDO exposed as rogue actor, UWE reputation protected." << std::endl;
        return true;
    }
    
    return false;
}

bool MissionLogic::executeMissionFinal() {
    std::cout << "\n--- FINAL MISSION: Siege of CyberCity ---" << std::endl;
    std::cout << " CyberCity HQ - AIDO's final assault begins!" << std::endl;
    
    if (current_objective == 0) {
        std::cout << " Defending Power Grid..." << std::endl;
        std::cout << " Firewall protocols activated!" << std::endl;
        std::cout << " Power Grid secured!" << std::endl;
        std::cout << "Next: Press SPACE to defend Hospital" << std::endl;
        return false;
    }
    else if (current_objective == 1) {
        std::cout << " Defending Hospital Systems..." << std::endl;
        std::cout << " Medical network protection engaged!" << std::endl;
        std::cout << " Hospital systems protected!" << std::endl;
        std::cout << "Next: Press SPACE to defend Airport" << std::endl;
        return false;
    }
    else if (current_objective == 2) {
        std::cout << " Defending Airport Infrastructure..." << std::endl;
        std::cout << " Flight control systems secured!" << std::endl;
        std::cout << " Airport systems defended!" << std::endl;
        std::cout << "Next: Press SPACE to deploy AI" << std::endl;
        return false;
    }
    else if (current_objective == 3) {
        std::cout << " Deploying Nyota AI..." << std::endl;
        if (game_state->getProgress().youss_alliance) {
            std::cout << " YOUSS Nyota AI activated!" << std::endl;
            std::cout << "✓ Predictive defense systems online!" << std::endl;
            game_state->addScore(50);
        } else {
            std::cout << " No YOUSS alliance - manual defense only!" << std::endl;
            std::cout << " Fighting without AI support!" << std::endl;
        }
        std::cout << "Next: Press SPACE for final assault" << std::endl;
        return false;
    }
    else if (current_objective == 4) {
        std::cout << " Locating AIDO's Control Server..." << std::endl;
        std::cout << " Triangulating signal source..." << std::endl;
        std::cout << " Server located: Abandoned UWE data center!" << std::endl;
        std::cout << "Next: Press SPACE for final confrontation" << std::endl;
        return false;
    }
    else if (current_objective == 5) {
        std::cout << " Final Assault on AIDO's Server!" << std::endl;
        std::cout << " Breaching control center..." << std::endl;
        std::cout << " AIDO's control server destroyed!" << std::endl;
        std::cout << " The Digital Siege is over!" << std::endl;
        std::cout << "\n VICTORY: Europe's smart cities are safe!" << std::endl;
        std::cout << "Final Score: " << game_state->getProgress().total_score << std::endl;
        return true;
    }
    
    return false;
}

void MissionLogic::completeObjective(int objective_index) {
    current_objective = objective_index + 1;
    game_state->addScore(25);
    std::cout << "[OBJECTIVE] Advanced to objective " << current_objective << std::endl;
}

void MissionLogic::failMission(const std::string& reason) {
    mission_active = false;
    game_state->completeMission(false);
    std::cout << " MISSION FAILED: " << reason << std::endl;
}

bool MissionLogic::checkObjectiveComplete(int /*objective_index*/) {
    return true;
}

// Simplified mini-games for interactive play
bool MissionLogic::rootkitScanMinigame() {
    std::cout << " Rootkit Scanner: AIDO signature detected!" << std::endl;
    return true;
}

bool MissionLogic::logDecryptionMinigame() {
    std::cout << " Decryption: Communications unlocked!" << std::endl;
    return true;
}

bool MissionLogic::packetAnalysisMinigame() {
    std::cout << " Packet Analysis: Suspicious patterns found!" << std::endl;
    return true;
}

bool MissionLogic::malwareReverseMinigame() {
    std::cout << " Malware Lab: Code structure revealed!" << std::endl;
    return true;
}

bool MissionLogic::honeypotSetupMinigame() {
    std::cout << " Honeypot: Traps deployed successfully!" << std::endl;
    return true;
}