
#include "apk_manager.h"
#include "vm_manager.h"
#include <dirent.h>
#include <cstdio>
#include <fstream>
#include <json-c/json.h>

static const char* DB_PATH = "/data/APKStation/apps/installed.json";

void ApkManager::Init() {}

bool ApkManager::InstallApk(const std::string& hostPath) {
    // 1. Copy APK to shared folder for VM
    std::string cmd = "cp "" + hostPath + "" /data/APKStation/shared/install.apk";
    system(cmd.c_str());
    // 2. Ask VM to install
    bool ok = VmManager::ExecPm("install -r /data/shared/install.apk");
    // 3. Parse package name and save icon
    if (ok) {
        // vm will output package name, we parse
    }
    return ok;
}

bool ApkManager::UninstallApk(const std::string& packageName) {
    return VmManager::ExecPm(("uninstall " + packageName).c_str());
}

std::vector<AppInfo> ApkManager::GetInstalledApps() {
    std::vector<AppInfo> apps;
    // Read from JSON DB written by VM
    FILE* f = fopen(DB_PATH, "r");
    if (!f) return apps;
    // Simplified - real code parses json
    fclose(f);
    // Fallback: ask VM
    return VmManager::ListPackages();
}

std::string ApkManager::GetPackageName(const std::string& apkPath) {
    // Use aapt stub - for now return filename
    return apkPath;
}
