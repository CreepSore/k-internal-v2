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

Player* kfw::ac::AcUtils::getLocalPlayer()
{
    return reinterpret_cast<Player*>(*reinterpret_cast<DWORD*>(ADDR_LOCALPLAYER));
}
