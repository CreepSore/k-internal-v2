#pragma once
#include "k-framework/k-framework.h"
#include "game-structs.h"
#include "game-addresses.h"

namespace kfw {
    namespace ac {
        class AcUtils {
            void setSpeed(float newSpeed);
            Player* getLocalPlayer();
        };
    }
}