#include "ui.hpp"
#include "game_state.hpp"
#include <iostream>
#include <sstream>
#include <vector>

UI::UI(GameStateManager* gs, sf::RenderWindow* win) 
    : game_state(gs), window(win), font_loaded(false) {
    
    setupFonts();
    setupColors();
    
    background_panel.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
    background_panel.setFillColor(sf::Color(15, 20, 30, 200));
    
    std::cout << "[UI] UI system initialized" << std::endl;
}

void UI::setupFonts() {
    font_loaded = false;
    
    // Try multiple font paths - same as working test
    std::vector<std::string> font_paths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/System/Library/Fonts/Arial.ttf",
        "/usr/share/fonts/TTF/arial.ttf",
        "assets/fonts/mono.ttf"
    };
    
    for (const auto& path : font_paths) {
        if (font.loadFromFile(path)) {
            font_loaded = true;
            std::cout << "[UI] ✅ Font loaded from: " << path << std::endl;
            break;
        }
    }
    
    if (!font_loaded) {
        std::cout << "[UI] ❌ No fonts found - text may not display properly" << std::endl;
    }
}

void UI::setupColors() {
    primary_color = sf::Color(0, 255, 150);    // Cyber green
    secondary_color = sf::Color(255, 100, 0);  // Warning orange
    accent_color = sf::Color(100, 200, 255);   // Electric blue
}

void UI::handleEvent(const sf::Event& /*event*/) {
    // Handle UI-specific events here
}

void UI::update(float /*delta_time*/) {
    // Update UI animations, effects, etc.
}

void UI::render() {
    switch (game_state->getState()) {
        case GameState::MAIN_MENU:
            renderMainMenu();
            break;
        case GameState::MISSION_SELECT:
            renderMissionSelect();
            break;
        case GameState::BRIEFING:
            renderMissionBriefing();
            break;
        case GameState::IN_MISSION:
            renderInMission();
            break;
        case GameState::FORENSICS_LAB:
            renderForensicsLab();
            break;
        case GameState::DEBRIEF:
            renderDebrief();
            break;
        case GameState::GAME_OVER:
            renderGameOver();
            break;
        case GameState::VICTORY:
            renderVictory();
            break;
    }
}

void UI::renderMainMenu() {
    // Create title text
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("CYBERFRONT: DIGITAL SIEGE");
    title.setCharacterSize(48);
    title.setFillColor(primary_color);
    title.setStyle(sf::Text::Bold);
    title.setPosition(200, 150);
    window->draw(title);
    
    // Create subtitle
    sf::Text subtitle;
    if (font_loaded) {
        subtitle.setFont(font);
    }
    subtitle.setString("The Insider War - 2032");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(accent_color);
    subtitle.setPosition(400, 220);
    window->draw(subtitle);
    
    // Create menu options
    sf::Text menu1;
    if (font_loaded) {
        menu1.setFont(font);
    }
    menu1.setString("1. START CAMPAIGN");
    menu1.setCharacterSize(28);
    menu1.setFillColor(sf::Color::White);
    menu1.setPosition(450, 350);
    window->draw(menu1);
    
    sf::Text menu2;
    if (font_loaded) {
        menu2.setFont(font);
    }
    menu2.setString("ESC. EXIT");
    menu2.setCharacterSize(24);
    menu2.setFillColor(sf::Color(150, 150, 150));
    menu2.setPosition(480, 400);
    window->draw(menu2);
    
    // Create status text
    sf::Text status;
    if (font_loaded) {
        status.setFont(font);
    }
    status.setString("PHILONO Task Force - Bournemouth HQ");
    status.setCharacterSize(18);
    status.setFillColor(secondary_color);
    status.setPosition(350, 600);
    window->draw(status);
    
    renderTrustMeters();
}

void UI::renderMissionSelect() {
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("MISSION SELECTION");
    title.setCharacterSize(36);
    title.setFillColor(primary_color);
    title.setPosition(400, 50);
    window->draw(title);
    
    const auto& missions = game_state->getMissions();
    for (size_t i = 0; i < missions.size(); ++i) {
        std::string mission_text = std::to_string(i + 1) + ". " + missions[i].title;
        
        sf::Color color = sf::Color::White;
        if (missions[i].state == MissionState::COMPLETED_SUCCESS) {
            color = primary_color;
            mission_text += " [COMPLETED]";
        } else if (missions[i].state == MissionState::COMPLETED_FAILURE) {
            color = secondary_color;
            mission_text += " [FAILED]";
        } else if (missions[i].state == MissionState::IN_PROGRESS) {
            color = accent_color;
            mission_text += " [IN PROGRESS]";
        }
        
        sf::Text mission;
        if (font_loaded) {
            mission.setFont(font);
        }
        mission.setString(mission_text);
        mission.setCharacterSize(24);
        mission.setFillColor(color);
        mission.setPosition(50, 150 + i * 80);
        window->draw(mission);
        
        sf::Text location;
        if (font_loaded) {
            location.setFont(font);
        }
        location.setString("Location: " + missions[i].location);
        location.setCharacterSize(16);
        location.setFillColor(sf::Color(180, 180, 180));
        location.setPosition(70, 175 + i * 80);
        window->draw(location);
    }
    
    sf::Text instruction;
    if (font_loaded) {
        instruction.setFont(font);
    }
    instruction.setString("Press number key to select mission, ESC to return");
    instruction.setCharacterSize(18);
    instruction.setFillColor(sf::Color(150, 150, 150));
    instruction.setPosition(50, 700);
    window->draw(instruction);
    
    renderTrustMeters();
}

void UI::renderInMission() {
    Mission* current = game_state->getCurrentMission();
    if (!current) return;
    
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("ACTIVE MISSION: " + current->title);
    title.setCharacterSize(28);
    title.setFillColor(secondary_color);
    title.setPosition(50, 30);
    window->draw(title);
    
    sf::Text location;
    if (font_loaded) {
        location.setFont(font);
    }
    location.setString("Location: " + current->location);
    location.setCharacterSize(20);
    location.setFillColor(accent_color);
    location.setPosition(50, 70);
    window->draw(location);
    
    sf::Text obj_title;
    if (font_loaded) {
        obj_title.setFont(font);
    }
    obj_title.setString("OBJECTIVES:");
    obj_title.setCharacterSize(24);
    obj_title.setFillColor(primary_color);
    obj_title.setPosition(50, 120);
    window->draw(obj_title);
    
    // Get current mission progress from game state
    int completed_objectives = 0;
    
    // Check story flags to determine progress
    if (game_state->getStoryFlag("rootkit_found")) {
        completed_objectives = std::max(completed_objectives, 2);
    }
    if (game_state->getStoryFlag("aido_identified")) {
        completed_objectives = std::max(completed_objectives, 3);
    }
    if (game_state->getStoryFlag("youss_contacted")) {
        completed_objectives = std::max(completed_objectives, 3);
    }
    
    // Also check mission score to determine progress
    if (current->score > 0) {
        completed_objectives = std::max(completed_objectives, static_cast<int>(current->objectives.size()));
    }
    
    // Use total score as a rough indicator of progress
    int score_progress = game_state->getProgress().total_score / 25;
    completed_objectives = std::max(completed_objectives, score_progress);
    
    for (size_t i = 0; i < current->objectives.size(); ++i) {
        std::string status = "[ ]";
        sf::Color color = sf::Color::White;
        
        // Show objectives as completed based on progress
        if (static_cast<int>(i) < completed_objectives) {
            status = "[✓]";
            color = primary_color;
        }
        // Highlight current objective
        else if (static_cast<int>(i) == completed_objectives) {
            status = "[→]";
            color = secondary_color;
        }
        
        std::string obj_text = status + " " + current->objectives[i];
        sf::Text objective;
        if (font_loaded) {
            objective.setFont(font);
        }
        objective.setString(obj_text);
        objective.setCharacterSize(18);
        objective.setFillColor(color);
        objective.setPosition(70, 160 + i * 30);
        window->draw(objective);
    }
    
    // Show mission controls
    sf::Text controls;
    if (font_loaded) {
        controls.setFont(font);
    }
    controls.setString("🎮 CONTROLS:");
    controls.setCharacterSize(20);
    controls.setFillColor(primary_color);
    controls.setPosition(50, 350);
    window->draw(controls);
    
    sf::Text space_hint;
    if (font_loaded) {
        space_hint.setFont(font);
    }
    space_hint.setString("SPACE - Advance to next objective");
    space_hint.setCharacterSize(16);
    space_hint.setFillColor(sf::Color::White);
    space_hint.setPosition(70, 380);
    window->draw(space_hint);
    
    sf::Text esc_hint;
    if (font_loaded) {
        esc_hint.setFont(font);
    }
    esc_hint.setString("ESC - Return to mission select");
    esc_hint.setCharacterSize(16);
    esc_hint.setFillColor(sf::Color::White);
    esc_hint.setPosition(70, 400);
    window->draw(esc_hint);
    
    // Show current progress
    sf::Text progress;
    if (font_loaded) {
        progress.setFont(font);
    }
    
    std::string progress_text = "Mission Progress: " + std::to_string(completed_objectives) + 
                               "/" + std::to_string(current->objectives.size()) + " objectives";
    if (completed_objectives < static_cast<int>(current->objectives.size())) {
        progress_text += " - Press SPACE to continue";
    } else {
        progress_text += " - Mission Complete!";
    }
    
    progress.setString(progress_text);
    progress.setCharacterSize(16);
    progress.setFillColor(accent_color);
    progress.setPosition(50, 450);
    window->draw(progress);
    
    // Show trust meters
    renderTrustMeters();
}

void UI::renderDebrief() {
    Mission* current = game_state->getCurrentMission();
    if (!current) return;
    
    std::string result = (current->state == MissionState::COMPLETED_SUCCESS) ? "SUCCESS" : "FAILURE";
    sf::Color result_color = (current->state == MissionState::COMPLETED_SUCCESS) ? primary_color : secondary_color;
    
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("MISSION " + result);
    title.setCharacterSize(48);
    title.setFillColor(result_color);
    title.setStyle(sf::Text::Bold);
    title.setPosition(450, 150);
    window->draw(title);
    
    sf::Text mission_name;
    if (font_loaded) {
        mission_name.setFont(font);
    }
    mission_name.setString(current->title);
    mission_name.setCharacterSize(24);
    mission_name.setFillColor(sf::Color::White);
    mission_name.setPosition(400, 220);
    window->draw(mission_name);
    
    sf::Text score;
    if (font_loaded) {
        score.setFont(font);
    }
    score.setString("Score: " + std::to_string(current->score));
    score.setCharacterSize(20);
    score.setFillColor(accent_color);
    score.setPosition(500, 280);
    window->draw(score);
    
    sf::Text total;
    if (font_loaded) {
        total.setFont(font);
    }
    total.setString("Total Score: " + std::to_string(game_state->getProgress().total_score));
    total.setCharacterSize(20);
    total.setFillColor(accent_color);
    total.setPosition(450, 320);
    window->draw(total);
    
    sf::Text instruction;
    if (font_loaded) {
        instruction.setFont(font);
    }
    instruction.setString("Press SPACE to continue");
    instruction.setCharacterSize(18);
    instruction.setFillColor(sf::Color(150, 150, 150));
    instruction.setPosition(450, 500);
    window->draw(instruction);
    
    renderTrustMeters();
}

void UI::renderVictory() {
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("VICTORY!");
    title.setCharacterSize(64);
    title.setFillColor(primary_color);
    title.setStyle(sf::Text::Bold);
    title.setPosition(500, 200);
    window->draw(title);
    
    sf::Text subtitle;
    if (font_loaded) {
        subtitle.setFont(font);
    }
    subtitle.setString("Europe's Smart Cities Are Safe!");
    subtitle.setCharacterSize(28);
    subtitle.setFillColor(accent_color);
    subtitle.setPosition(350, 300);
    window->draw(subtitle);
    
    sf::Text final_score;
    if (font_loaded) {
        final_score.setFont(font);
    }
    final_score.setString("Final Score: " + std::to_string(game_state->getProgress().total_score));
    final_score.setCharacterSize(24);
    final_score.setFillColor(sf::Color::White);
    final_score.setPosition(450, 400);
    window->draw(final_score);
    
    if (game_state->getProgress().youss_alliance) {
        sf::Text alliance;
        if (font_loaded) {
            alliance.setFont(font);
        }
        alliance.setString("YOUSS Alliance: ACTIVE");
        alliance.setCharacterSize(20);
        alliance.setFillColor(primary_color);
        alliance.setPosition(400, 450);
        window->draw(alliance);
    }
    
    sf::Text instruction;
    if (font_loaded) {
        instruction.setFont(font);
    }
    instruction.setString("Press SPACE or ESC to return to main menu");
    instruction.setCharacterSize(18);
    instruction.setFillColor(sf::Color(150, 150, 150));
    instruction.setPosition(350, 550);
    window->draw(instruction);
}

void UI::renderGameOver() {
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("MISSION FAILED");
    title.setCharacterSize(48);
    title.setFillColor(secondary_color);
    title.setStyle(sf::Text::Bold);
    title.setPosition(450, 300);
    window->draw(title);
    
    sf::Text subtitle;
    if (font_loaded) {
        subtitle.setFont(font);
    }
    subtitle.setString("The Digital Siege Continues...");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setPosition(400, 380);
    window->draw(subtitle);
}

void UI::renderMissionBriefing() {
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("MISSION BRIEFING");
    title.setCharacterSize(36);
    title.setFillColor(primary_color);
    title.setPosition(450, 200);
    window->draw(title);
}

void UI::renderForensicsLab() {
    sf::Text title;
    if (font_loaded) {
        title.setFont(font);
    }
    title.setString("FORENSICS LAB");
    title.setCharacterSize(36);
    title.setFillColor(primary_color);
    title.setPosition(450, 200);
    window->draw(title);
}

void UI::renderTrustMeters() {
    const auto& progress = game_state->getProgress();
    
    sf::RectangleShape trust_bg(sf::Vector2f(200, 140));
    trust_bg.setPosition(950, 50);
    trust_bg.setFillColor(sf::Color(0, 0, 0, 150));
    trust_bg.setOutlineColor(primary_color);
    trust_bg.setOutlineThickness(2);
    window->draw(trust_bg);
    
    sf::Text trust_title;
    if (font_loaded) {
        trust_title.setFont(font);
    }
    trust_title.setString("TRUST LEVELS");
    trust_title.setCharacterSize(16);
    trust_title.setFillColor(primary_color);
    trust_title.setPosition(960, 60);
    window->draw(trust_title);
    
    sf::Text uk_label;
    if (font_loaded) {
        uk_label.setFont(font);
    }
    uk_label.setString("UK: " + std::to_string(progress.trust_uk) + "%");
    uk_label.setCharacterSize(14);
    uk_label.setFillColor(sf::Color::White);
    uk_label.setPosition(960, 85);
    window->draw(uk_label);
    
    sf::Text youss_label;
    if (font_loaded) {
        youss_label.setFont(font);
    }
    youss_label.setString("YOUSS: " + std::to_string(progress.trust_youss) + "%");
    youss_label.setCharacterSize(14);
    youss_label.setFillColor(sf::Color::White);
    youss_label.setPosition(960, 105);
    window->draw(youss_label);
    
    sf::Text eu_label;
    if (font_loaded) {
        eu_label.setFont(font);
    }
    eu_label.setString("EU: " + std::to_string(progress.trust_eu) + "%");
    eu_label.setCharacterSize(14);
    eu_label.setFillColor(sf::Color::White);
    eu_label.setPosition(960, 125);
    window->draw(eu_label);
    
    if (progress.youss_alliance) {
        sf::Text alliance;
        if (font_loaded) {
            alliance.setFont(font);
        }
        alliance.setString("YOUSS ALLIED");
        alliance.setCharacterSize(12);
        alliance.setFillColor(primary_color);
        alliance.setPosition(960, 145);
        window->draw(alliance);
    }
}

void UI::renderMissionProgress() {
    // Implementation for mission progress display
}

void UI::renderCharacterInfo() {
    // Implementation for character information display
}

void UI::renderTerminalEffect(const std::string& text, float x, float y) {
    sf::Text terminal;
    if (font_loaded) {
        terminal.setFont(font);
    }
    terminal.setString(text);
    terminal.setCharacterSize(16);
    terminal.setFillColor(primary_color);
    terminal.setPosition(x, y);
    window->draw(terminal);
}

sf::Text UI::createText(const std::string& content, float x, float y, int size) {
    sf::Text text;
    if (font_loaded) {
        text.setFont(font);
    }
    text.setString(content);
    text.setCharacterSize(size);
    text.setPosition(x, y);
    return text;
}