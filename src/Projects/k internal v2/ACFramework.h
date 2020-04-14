#pragma once
#include "k-framework/k-framework.h"
#include "game-structs.h"
#include "game-addresses.h"

namespace kfw {
    namespace ac {
        class AcUtils {
        public:
            static void setSpeed(float newSpeed);
            static Player* getLocalPlayer();
        };
    }
}