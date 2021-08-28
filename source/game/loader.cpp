#include <vector>
#include <utility>

#include "utilities/loader.hpp"
#include "utilities/logger.hpp"

register_logger()

using namespace ksf::utilities;

void contentLoader::loadSprites(engine::managers::assetsManager* manager)
{
    const std::vector<std::pair<std::string, std::string>> sprites =
    {
        // Main Menu
        {"Main Menu Play 01", "mainMenu/play01.png"},
        {"Main Menu Play 02", "mainMenu/play02.png"},
        
        {"Main Menu Quit 01", "mainMenu/quit01.png"},
        {"Main Menu Quit 02", "mainMenu/quit02.png"},

        {"Main Menu Select 01", "mainMenu/select01.png"},
        {"Main Menu Select 02", "mainMenu/select02.png"},
        {"Main Menu Select 03", "mainMenu/select03.png"},
        {"Main Menu Select 04", "mainMenu/select04.png"},

        {"Main Menu Title 01", "mainMenu/title01.png"},
        {"Main Menu Title 02", "mainMenu/title02.png"},

        // Instructions
        {"Instructions 01", "instructions/instructions01.png"},
        {"Instructions 02", "instructions/instructions02.png"},

        // Beach background
        {"Beach Background 01", "beach/1.png"},
        {"Beach Background 02", "beach/2.png"},
        {"Beach Background 03", "beach/3.png"},
        {"Beach Background 04", "beach/4.png"},
        {"Beach Background 05", "beach/5.png"}
    };

    for(const auto &sprite: sprites)
        manager->requestSprite(sprite.first, sprite.second);
}

void contentLoader::loadAnimations(engine::managers::animationsManager* animationsManagerPtr, engine::managers::assetsManager* assetsManaterPtr)
{
    animationsManagerPtr->requestAnimation("Main Menu Title", {
        { "Main Menu Title 01", 500 },
        { "Main Menu Title 02", 500 }
    });
    animationsManagerPtr->requestAnimation("Main Menu Play", {
        { "Main Menu Play 01", 500 },
        { "Main Menu Play 02", 500 }
    });
    animationsManagerPtr->requestAnimation("Main Menu Quit", {
        { "Main Menu Quit 01", 500 },
        { "Main Menu Quit 02", 500 }
    });
    animationsManagerPtr->requestAnimation("Main Menu Select On", {
        { "Main Menu Select 01", 200 },
        { "Main Menu Select 04", 200 }
    });
    animationsManagerPtr->requestAnimation("Main Menu Select Off", {
        { "Main Menu Select 02", 200 },
        { "Main Menu Select 03", 200 }
    });

    animationsManagerPtr->requestAnimation("BeachBackground",{
        {"Beach Background 01", 500},
        {"Beach Background 02", 500},
        {"Beach Background 03", 500},
        {"Beach Background 04", 500},
        {"Beach Background 05", 500}
    });
    
    animationsManagerPtr->requestAnimation("Instructions", {
        { "Instructions 01", 500 },
        { "Instructions 02", 500 },
    });
}