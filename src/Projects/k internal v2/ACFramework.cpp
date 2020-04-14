#include "ACFramework.h"
#include "game-addresses.h"

void kfw::ac::AcUtils::setSpeed(float newSpeed)
{
    *reinterpret_cast<float*>(ADDR_MAX_PLAYER_SPEED) = newSpeed;
    getLocalPlayer()->maxSpeed = newSpeed;
}

Player* kfw::ac::AcUtils::getLocalPlayer()
{
    return reinterpret_cast<Player*>(*reinterpret_cast<DWORD*>(ADDR_LOCALPLAYER));
}
