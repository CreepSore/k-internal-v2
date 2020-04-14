#pragma once
#include <Windows.h>

typedef unsigned char uchar;
typedef unsigned int uint;

struct Vec3f { /* Vector with 3 floats */
    float x;
    float y;
    float z;
};

struct AttackStats {
    DWORD knifeAttackCount;
    DWORD pistolAttackCount;
    DWORD rifleAttackCount;
    DWORD shotgunAttackCount;
    DWORD mpAttackCount;
    DWORD sniperAttackCount;
    DWORD arAttackCount;
    DWORD field_0x1c;
    DWORD grenadeAttackCount;
    DWORD akimboAttackCount;
};

struct Player {
    DWORD* vTable;
    struct Vec3f cameraPosition;
    uchar field_0x10[24];
    struct Vec3f velocity;
    struct Vec3f position;
    struct Vec3f angles;
    uchar field_0x4c[4];
    float maxSpeed;
    uchar field_0x54[8];
    float eyeHeight;
    float maxEyeHeight;
    uchar field_0x64[5];
    bool onGround;
    uchar field_0x6a[3];
    bool moving;
    DWORD field_0x6e[34];
    int health;
    int armor;
    DWORD field_0xfe[34];
    struct AttackStats attackStats;
    DWORD field_0x1ae[13];
    uint playerId;
    DWORD field_0x1e6[15];
    uchar field_0x222;
    char* name;
};

