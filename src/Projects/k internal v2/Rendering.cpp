#include "k-framework/k-framework.h"
#include "ACFramework.h"
#include "Rendering.h"
#include <gl/GL.h>


kfw::ac::TeleportHack::TeleportHack() : IBaseHack("AC_TELEPORT", "Teleport") { }

void kfw::ac::TeleportHack::onRender() {
    auto lp = kfw::ac::AcUtils::getLocalPlayer();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glPopMatrix();
    glPopAttrib();
}

void kfw::ac::TeleportHack::onRegister()
{
}

void kfw::ac::TeleportHack::onUnregister()
{
}

bool kfw::ac::TeleportHack::onEvent(std::string event, void* args)
{
    if (event == "onRender") {
        onRender();
    }
    return true;
}
