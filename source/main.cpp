#include "utilities/logger.hpp"

#include "graphics/core.hpp"
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
    graphics::core game_core(800,600,std::make_shared<ui::menu>());
    game_core.initialize();
    game_core.execute();
    return 0;
}
