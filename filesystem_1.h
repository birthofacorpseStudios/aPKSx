
#pragma once
#include <vector>
#include <string>

namespace FileSystem {
    void Init();
    std::vector<std::string> ScanForApks();
    bool FileExists(const std::string& path);
}
