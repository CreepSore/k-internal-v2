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

nlohmann::json constructPlayerData() {
    Player* lp = kfw::ac::AcUtils::getLocalPlayer();
    auto posObj = nlohmann::json::object({ {"x", lp->position.x}, {"y", lp->position.y}, {"z", lp->position.z} });
    auto velObj = nlohmann::json::object({ {"x", lp->velocity.x}, {"y", lp->velocity.y}, {"z", lp->velocity.z} });
    return nlohmann::json::object({ { "health", lp->health }, { "armor", lp->armor }, { "position", posObj }, { "speed", lp->maxSpeed }, { "velocity", velObj }, { "eyeHeight", lp->eyeHeight } });
}

BOOL __stdcall mainThread(LPVOID module) {
    kfw::core::DatabridgeClient dc = kfw::core::DatabridgeClient("78.46.41.219", 1328);
    dc.establishConnection(true);

    kfw::core::Utils::setupConsole();
    logger.log("Loaded Hack!", "mainThread");
    auto hookManager = kfw::core::Factory::getDefaultHookManager();
    auto hackManager = kfw::core::Factory::getDefaultHackManager();

    hackManager->registerHack(new kfw::ac::TeleportHack());
    kfw::core::DatabridgePacket packet;
    while (!GetAsyncKeyState(VK_NUMPAD0)) {
        hackManager->onEvent("MT_LOOP", nullptr);
        dc.sendData(kfw::core::DatabridgePacket("PLAYER", constructPlayerData()));
        
        if (dc.receivePacket(packet)) {
            if (packet.type == "SET_PLAYER_PROPERTY") {
                try {
                    std::string target = packet.data.value("target", "invalid");
                    if (target == "health") {
                        try {
                            int value = packet.data.value("value", -1);
                            if (value > 0) {
                                kfw::ac::AcUtils::getLocalPlayer()->health = value;
                            }
                        }
                        catch (...) {}
                    }

                    if (target == "armor") {
                        int value = packet.data.value("value", -1);
                        if (value > 0) {
                            kfw::ac::AcUtils::getLocalPlayer()->armor = value;
                        }
                    }

                    if (target == "speed") {
                        int value = packet.data.value("value", -1);
                        if (value > 0) {
                            kfw::ac::AcUtils::setSpeed(value);
                        }
                    }

                    if (target == "eye-height") {
                        float value = packet.data.value<float>("value", -1);
                        if (value > 0) {
                            kfw::ac::AcUtils::getLocalPlayer()->eyeHeight = value;
                            kfw::ac::AcUtils::getLocalPlayer()->maxEyeHeight = value;
                        }
                    }
                }
                catch (...) { }
            }
        }

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

