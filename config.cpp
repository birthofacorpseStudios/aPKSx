
#include "config.h"
#include <fstream>
#include <sys/stat.h>

static Config g_cfg;
Config& Config::Get(){ return g_cfg; }

void Config::Load(){
    mkdir("/data/APKStation", 0777);
    FILE* f = fopen("/data/APKStation/config.json","r");
    if(!f) return;
    fseek(f,0,SEEK_END); long sz=ftell(f); fseek(f,0,SEEK_SET);
    std::string s; s.resize(sz); fread(s.data(),1,sz,f); fclose(f);
    // naive parse for v1 - look for values
    auto findF = [&](const char* key, float& out){ auto p=s.find(key); if(p!=std::string::npos){ sscanf(s.c_str()+p, "%*[^:]: %f", &out);} };
    findF("\"pointerSensitivity\"", pointerSensitivity);
    findF("\"touchpadSensitivity\"", touchpadSensitivity);
    findF("\"displayScale\"", displayScale);
}
void Config::Save(){
    mkdir("/data/APKStation", 0777);
    FILE* f = fopen("/data/APKStation/config.json","w");
    if(!f) return;
    fprintf(f, "{\n");
    fprintf(f, "  \"pointerSensitivity\": %.2f,\n", pointerSensitivity);
    fprintf(f, "  \"touchpadSensitivity\": %.2f,\n", touchpadSensitivity);
    fprintf(f, "  \"displayScale\": %.2f,\n", displayScale);
    fprintf(f, "  \"displayFit\": %d,\n", displayFit);
    fprintf(f, "  \"useTouchpadAsTouch\": %s,\n", useTouchpadAsTouch?"true":"false");
    fprintf(f, "  \"deadzone\": %d\n", deadzone);
    fprintf(f, "}\n");
    fclose(f);
    chmod("/data/APKStation/config.json", 0777);
}
