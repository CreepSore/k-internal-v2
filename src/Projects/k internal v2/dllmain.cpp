#include <sstream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "k-framework/k-framework.h"
#include "json.hpp"
#include "ACFramework.h"
#include "message_types.h"
#include "game-structs.h"
#include "Hacks.h"

auto logger = kfw::core::Logger();

void __cdecl addmsg(uint32_t messageType, char* flags, void* addData) {
    auto hook = kfw::core::Factory::getDefaultHookManager()->getHookByIdentifier("AC_ADDMSG")->header;
    reinterpret_cast<void(__cdecl*)(uint32_t, char*, ...)>(hook)(messageType, flags, addData);
}

void fatal(char* msg) {
    logger.log(msg, "AC_FATAL");
    return reinterpret_cast<void(*)(char*)>(kfw::core::Factory::getDefaultHookManager()->getHookByIdentifier("AC_FATAL")->header)(msg);
}

nlohmann::json constructPlayerData() {
    Player* lp = kfw::ac::AcUtils::getLocalPlayer();
    auto posObj = nlohmann::json::object({ {"x", lp->position.x}, {"y", lp->position.y}, {"z", lp->position.z} });
    auto velObj = nlohmann::json::object({ {"x", lp->velocity.x}, {"y", lp->velocity.y}, {"z", lp->velocity.z} });
    return nlohmann::json::object({ { "health", lp->health }, {"armor", lp->armor}, {"position", posObj}, {"velocity", velObj } });
}

BOOL __stdcall mainThread(LPVOID module) {
    kfw::core::DatabridgeClient dc = kfw::core::DatabridgeClient("78.46.41.219", 1328);
    dc.establishConnection(true);

    kfw::core::Utils::setupConsole();
    logger.log("Loaded Hack!", "mainThread");
    auto hookManager = kfw::core::Factory::getDefaultHookManager();
    auto hackManager = kfw::core::Factory::getDefaultHackManager();

    //hookManager->registerHook(new kfw::core::HookData((void*)(0x4204b0), addmsg, 6, "AC_ADDMSG", "addmsg"));
    //hookManager->registerHook(new kfw::core::HookData((void*)(0x4728f0), fatal, 6, "AC_FATAL", "fatal"));
    //hookManager->hookAll();

    hackManager->registerHack(new kfw::ac::TeleportHack());

    while (!GetAsyncKeyState(VK_NUMPAD0)) {
        hackManager->onEvent("MT_LOOP", nullptr);
        dc.sendData(kfw::core::DatabridgePacket("PLAYER", constructPlayerData()));
        
        Sleep(100);
    }

    logger.log("Unloading Hack ...", "mainThread");
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

