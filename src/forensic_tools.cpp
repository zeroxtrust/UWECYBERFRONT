#include "forensic_tools.hpp"
#include <iostream>

bool ForensicTools::scanForRootkit(const std::string& data) {
    std::cout << "Scanning for rootkits...\n";
    return data.find("AIDO_SIG") != std::string::npos;
}

std::string ForensicTools::loadPacketCapture(const std::string& path) {
    return "dummy_packet_log_with_AIDO_SIG";
}

void ForensicTools::decryptLogs(const std::string& path) {
    std::cout << "Decrypting log: " << path << std::endl;
} 