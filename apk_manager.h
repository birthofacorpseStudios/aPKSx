
#pragma once
#include "../ui/launcher.h"
#include <vector>
#include <string>

namespace ApkManager {
    void Init();
    bool InstallApk(const std::string& hostPath);
    bool UninstallApk(const std::string& packageName);
    std::vector<AppInfo> GetInstalledApps();
    std::string GetPackageName(const std::string& apkPath);
}
