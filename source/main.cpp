#include "utilities/logger.hpp"

#include "engine/core.hpp"
#include "ui/menu.hpp"

#ifdef WINDOWS
#include <windows.h>
#endif

register_logger();

#ifdef WINDOWS
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
    graphics::core gameCore(800,600);
    
    gameCore.getChild<engine::assetsManager>("Assets Manager")->requestSprite("Test", "Test.png");
    gameCore.getChild<engine::viewsManager>("Views Manager")->registerView(std::make_shared<ui::menu>("Main"));

    gameCore.initialize();
    gameCore.execute();
    return 0;
}
