#pragma once
#include <string>

namespace ForensicTools {
    bool scanForRootkit(const std::string& data);
    std::string loadPacketCapture(const std::string& path);
    void decryptLogs(const std::string& path);
}