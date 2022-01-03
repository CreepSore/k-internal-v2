#include "ACFramework.h"
#include "game-addresses.h"

void kfw::ac::AcUtils::setSpeed(float newSpeed)
{
    DWORD oldProt, temp;
    VirtualProtect(LPVOID(ADDR_MAX_PLAYER_SPEED), sizeof(float), PAGE_EXECUTE_READWRITE, &oldProt);
    *reinterpret_cast<float*>(ADDR_MAX_PLAYER_SPEED) = newSpeed;
    VirtualProtect(LPVOID(ADDR_MAX_PLAYER_SPEED), sizeof(float), oldProt, &temp);
    getLocalPlayer()->maxSpeed = newSpeed;
}

void kfw::ac::AcUtils::printToChat(const char* msg, ...)
{
    char buffer[255];
    va_list args;
    va_start(args, msg);
    vsnprintf_s(buffer, 255, msg, args);
    reinterpret_cast<void(__cdecl*)(char*)>(ADDR_FUNC_PRINT_TO_CHAT)(buffer);
    va_end(args);
}

Player* kfw::ac::AcUtils::getLocalPlayer()
{
    return reinterpret_cast<Player*>(*reinterpret_cast<DWORD*>(ADDR_LOCALPLAYER));
}
