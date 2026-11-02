
#include "vm_manager.h"
#include <pthread.h>
#include <unistd.h>

static pthread_t qemuThread;
static bool vmRunning = false;

static void* qemuMain(void*) {
    // This is the command that boots Android-x86 inside PS4
    // Requires /data/APKStation/android_system.img to exist
    // qemu-system-x86_64 -kernel /data/APKStation/kernel -initrd /data/APKStation/ramdisk.img
    // -hda /data/APKStation/android_system.img -hdb /data/APKStation/android_data.img
    // -append "root=/dev/ram0 androidboot.hardware=android_x86_64" -vnc :0 -shared-folder /data/APKStation/shared
    // For v1 we stub this - real implementation uses sceKernel + QEMU port
    while (vmRunning) sleep(1);
    return nullptr;
}

void VmManager::Init() {
    vmRunning = true;
    pthread_create(&qemuThread, nullptr, qemuMain, nullptr);
}

void VmManager::Shutdown() {
    vmRunning = false;
    pthread_join(qemuThread, nullptr);
}

bool VmManager::ExecPm(const std::string& cmd) {
    // Communicate to VM via socket /data/APKStation/shared/cmd.sock
    // Write cmd to /data/APKStation/shared/pm_cmd.txt and wait for result
    return true;
}

std::vector<AppInfo> VmManager::ListPackages() {
    return {}; // parse pm list packages output
}

void VmManager::LaunchPackage(const std::string& pkg) {
    ExecPm(("am start -n " + pkg + "/.MainActivity").c_str());
}

void VmManager::SendBack() {
    InjectKey(4); // KEYCODE_BACK
}

void VmManager::InjectTouch(int type, float x, float y) {
    // Send to VM: sendevent /dev/input/event2
    char buf[128];
    snprintf(buf, sizeof(buf), "tap %f %f %d", x, y, type);
    ExecPm(buf);
}

void VmManager::InjectKey(int keycode) {
    char buf[64];
    snprintf(buf, sizeof(buf), "keyevent %d", keycode);
    ExecPm(buf);
}

void* VmManager::GetFramebuffer() {
    // Return pointer to /dev/fb0 mmap shared with QEMU
    return nullptr;
}
