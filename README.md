## README.md

# UWECYBERFRONT: Digital Siege

**The Insider War - 2032**

A strategic tactical cyber wargame with forensics elements, built in C++ with SFML.

## Game Overview

Set in the year 2032, CYBERFRONT: Digital Siege immerses players into a high-stakes cyberwar led by a rogue academic hacker known as **AIDO**. Players command **PHILONO**, an elite EU cyber defence team, and work alongside **YOUSS**, a pan-African AI-powered alliance, to uncover and prevent a global digital catastrophe.

### Key Features

- **5 Story-Driven Missions** with realistic cybersecurity scenarios
- **Digital Forensics Gameplay** - rootkit scanning, log decryption, packet analysis
- **Strategic Diplomacy System** - choices affect trust with UK, EU, and YOUSS
- **Multiple Endings** based on transparency vs cover-up decisions
- **Educational Content** - real cybersecurity concepts and procedures
- **Cross-Platform** - Windows, Linux, macOS support

## Characters & Factions

### PHILONO (EU Cyber Defense)
- **PHILONO** - Silent operator and task force leader (Player)
- **SAGE** - Elena Vos, Cryptography Expert
- **BYTE** - AI Assistant for forensics and analysis
- **SPINNER** - Jamal Beckett, Social Engineering Analyst

### AIDO (Antagonist)
- **Dr. Demetri Dobrev** - Former UWE lecturer turned rogue Russian operative
- Mastermind behind the Digital Siege using academic insider access

### YOUSS (African Cyber Alliance)
- **Dr. Yousef E** - Founder of Nyota AI predictive threat detection
- Potential ally depending on player diplomatic choices

## Mission Structure

1. **Academic Breach** - Investigate UWE network infiltration and rootkit discovery
2. **Code of Deceit** - Reverse engineer malware and identify AIDO's signature
3. **University VPN Breach** - Deploy honeypots and establish international alliances
4. **The Faculty Firewall** - Critical diplomatic decisions at NCSC headquarters
5. **Siege of CyberCity** - Final confrontation defending Europe's smart infrastructure

## Technical Stack
- **Language**: C++20
- **Graphics**: SFML 2.5+
- **Build System**: CMake 3.16+
- **Data Format**: JSON (with fallback support)
- **Architecture**: Modular game engine with state management

## Quick Start

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt install build-essential cmake libsfml-dev

# Arch Linux  
sudo pacman -S base-devel cmake sfml

# macOS
brew install cmake sfml
```

### Build & Run
```bash
mkdir build && cd build
cmake ..
make -j4
./cyberfront
```

Or use the build script:
```bash
./build_and_run.sh
```

## Controls

- **Main Menu**: `1` Start Campaign, `ESC` Exit
- **Mission Selection**: `1-5` Select mission, `ESC` Return  
- **In Mission**: `SPACE` Continue/Progress
- **Debrief**: `SPACE` Continue to next mission

## Educational Use

This game is designed for cybersecurity education and demonstrates:

- **Digital Forensics** - File analysis, log examination, metadata extraction
- **Incident Response** - Threat detection, containment, and mitigation
- **Insider Threats** - Academic and institutional vulnerabilities
- **International Cooperation** - Trust building in cybersecurity alliances
- **Ethical Decision Making** - Transparency vs operational security

Perfect for:
- University cybersecurity courses
- NCSC CyberFirst programs  
- Professional security training
- Independent learning

## Development

### VS Code Setup
1. Install required extensions: C/C++, CMake Tools
2. Open project: `code .`
3. Configure: `Ctrl+Shift+P` → "CMake: Configure"
4. Build: `Ctrl+Shift+B`
5. Run: `F5`

### Architecture
```
Engine (SFML) → GameStateManager → MissionLogic
     ↓              ↓                ↓
    UI          Progress         ForensicTools
               Tracking         (Mini-games)
```

## Credits

- **Concept & Story**: Yousef
- **Game Design**: Based on NCSC and academic cybersecurity programs
- **Technical Implementation**: C++20, SFML, CMake ecosystem
- **Educational Framework**: Real-world cybersecurity incident response

## License

Educational use. Please maintain attribution and educational purpose in derivatives.
""""""""""""""""""""""""
██╗   ██╗██╗    ██╗███████╗     ██████╗██╗   ██╗██████╗ ███████╗██████╗ ███████╗██████╗  ██████╗ ███╗   ██╗████████╗
██║   ██║██║    ██║██╔════╝    ██╔════╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔══██╗██╔════╝██╔══██╗██╔═══██╗████╗  ██║╚══██╔══╝
██║   ██║██║ █╗ ██║█████╗      ██║      ╚████╔╝ ██████╔╝█████╗  ██████╔╝█████╗  ██████╔╝██║   ██║██╔██╗ ██║   ██║   
██║   ██║██║███╗██║██╔══╝      ██║       ╚██╔╝  ██╔══██╗██╔══╝  ██╔══██╗██╔══╝  ██╔══██╗██║   ██║██║╚██╗██║   ██║   
╚██████╔╝╚███╔███╔╝███████╗    ╚██████╗   ██║   ██████╔╝███████╗██║  ██║██║     ██║  ██║╚██████╔╝██║ ╚████║   ██║   
 ╚═════╝  ╚══╝╚══╝ ╚══════╝     ╚═════╝   ╚═╝   ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   
                                                                                           """"""""""""""""""""""""                              

![UWECyberfront](https://github.com/user-attachments/assets/f41aa9b5-a9da-4592-bc2b-2cce32784f57)
