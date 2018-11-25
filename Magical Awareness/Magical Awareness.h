#define PLUGIN_SETUP(NAME, LOAD_FUNC) \
void* g_LocalPlayer; \
PSDK_CONTEXT SDK_CONTEXT_GLOBAL; \
\
void __cdecl OnLoad(void* UserData);\
\
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {\
    CheckSDK(NAME);\
    \
    SdkRegisterOnLoad(LOAD_FUNC, NULL);\
    \
    return true;\
}

#define CheckSDK(NAME) \
UNREFERENCED_PARAMETER(hinstDLL); \
\
if (fdwReason != DLL_PROCESS_ATTACH) \
return FALSE; \
\
SDK_EXTRACT_CONTEXT(lpvReserved); \
if (!SDK_CONTEXT_GLOBAL || !SDKSTATUS_SUCCESS(SdkNotifyLoadedModule(NAME, SDK_VERSION))) { \
    return FALSE; \
}

void __cdecl DrawGameScene(void* UserData);
bool __cdecl PrintHealth(void* Object, unsigned int NetworkID, void* UserData);
