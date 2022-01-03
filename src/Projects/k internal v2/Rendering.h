#pragma once
#include "k-framework/k-framework.h"

namespace kfw {
    namespace ac {
        class TeleportHack : public kfw::core::IBaseHack {
        private:
            void onRender();
        public:
            TeleportHack();

            // Geerbt über IBaseHack
            virtual void onRegister() override;
            virtual void onUnregister() override;
            virtual bool onEvent(std::string event, void* args) override;
        };
    }
}