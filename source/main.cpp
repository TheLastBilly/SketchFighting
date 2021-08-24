#include "utilities/logger.hpp"

#include "graphics/core.hpp"
#include "ui/main_menu.hpp"

register_logger();

int main(int argc, char const *argv[])
{
    info("All good so far");
    graphics::core game_core(800,600,std::make_shared<ui::main>());
    game_core.initialize();
    game_core.execute();
    return 0;
}
