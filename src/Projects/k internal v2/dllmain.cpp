#include "k-framework/k-framework.h"
#include "game-structs.h"
#include <sstream>

auto logger = kfw::core::Logger();

void __cdecl addmsg(uint32_t messageType, char* flags, void* ad1, void* ad2, void* ad3, void* ad4, void* ad5, void* ad6, void* ad7, void* ad8) {
    if (messageType != 0xF && messageType != 47) {
        std::stringstream ss;
        ss << "Invalid Message-Type: " << messageType;
        logger.log(ss.str(), "AC_ADDMSG");
    }
    auto hook = kfw::core::Factory::getDefaultHookManager()->getHookByIdentifier("AC_ADDMSG")->header;
    size_t len = strlen(flags);

    switch (len) {
    case 0:
    case 1:
        reinterpret_cast<void(__cdecl*)(uint32_t, char*, ...)>(hook)(messageType, flags);
        break;
    
    default:
        std::stringstream ss;
        ss << "Invalid packet length: " << len;
        logger.log(ss.str(), "AC_ADDMSG");
        break;
    }
}

void fatal(char* msg) {
    logger.log(msg, "AC_FATAL");
}

BOOL __stdcall mainThread(LPVOID module) {
    kfw::core::Utils::setupConsole();
    auto hookManager = kfw::core::Factory::getDefaultHookManager();

    hookManager->registerHook(new kfw::core::HookData((void*)(0x4204B0), addmsg, 6, "AC_ADDMSG", "addmsg"));
    hookManager->registerHook(new kfw::core::HookData((void*)(0x4728f0), fatal, 6, "AC_FATAL", "fatal"));
    hookManager->hookAll();

    Player** lp = (Player**)(0x50f4f4);

    while (!GetAsyncKeyState(VK_NUMPAD0)) {
        Sleep(100);
    }

    kfw::core::Factory::cleanup();
    Beep(1000, 500);
    FreeLibraryAndExitThread(HMODULE(module), 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(mainThread), LPVOID(hModule), 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

