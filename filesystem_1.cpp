
#include "filesystem.h"
#include <dirent.h>
#include <sys/stat.h>

void FileSystem::Init() {
    mkdir("/data/APKStation", 0777);
    mkdir("/data/APKStation/shared", 0777);
    mkdir("/data/APKStation/apps", 0777);
}

bool FileSystem::FileExists(const std::string& p) {
    struct stat st;
    return stat(p.c_str(), &st)==0;
}

static void scanRec(const std::string& base, std::vector<std::string>& out) {
    DIR* d = opendir(base.c_str());
    if (!d) return;
    dirent* ent;
    while ((ent = readdir(d)) != nullptr) {
        std::string name = ent->d_name;
        if (name=="."||name=="..") continue;
        std::string full = base + "/" + name;
        if (ent->d_type == DT_DIR) {
            if (base.size() < 4) scanRec(full, out); // limit depth for usb scan
        } else {
            if (name.size()>4 && name.substr(name.size()-4)==".apk") out.push_back(full);
        }
    }
    closedir(d);
}

std::vector<std::string> FileSystem::ScanForApks() {
    std::vector<std::string> out;
    const char* roots[] = {"/mnt/usb0", "/mnt/usb1", "/data", "/mnt/hdd0/packages", "/data/CUSA00000", "/data/homebrew"};
    for (auto r: roots) scanRec(r, out);
    return out;
}
