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

        // Hammer Guy
        {"Hammer Guy Jumping 01", "HammerGuy/jumping01.png"},
        {"Hammer Guy Jumping 02", "HammerGuy/jumping02.png"},
        {"Hammer Guy Name 01", "HammerGuy/name01.png"},
        {"Hammer Guy Name 02", "HammerGuy/name02.png"},
        {"Hammer Guy Idle 01", "HammerGuy/standing01.png"},
        {"Hammer Guy Idle 02", "HammerGuy/standing02.png"},
        {"Hammer Guy Walking 01", "HammerGuy/walking01.png"},
        {"Hammer Guy Walking 02", "HammerGuy/walking02.png"},
        {"Hammer Guy Walking 03", "HammerGuy/walking03.png"},
        {"Hammer Guy Block 01", "HammerGuy/block01.png"},
        {"Hammer Guy Block 02", "HammerGuy/block02.png"},
        {"Hammer Guy Ground 01", "HammerGuy/ground01.png"},
        {"Hammer Guy Ground 02", "HammerGuy/ground02.png"},
        {"Hammer Guy Ground 03", "HammerGuy/ground03.png"},
        {"Hammer Guy Hit 01", "HammerGuy/hit01.png"},
        {"Hammer Guy Hit 02", "HammerGuy/hit02.png"},

        // Miso
        {"Miso Jumping 01", "Miso/jump/1.png"},
        {"Miso Jumping 02", "Miso/jump/2.png"},
        {"Miso Name 01", "Miso/name/1.png"},
        {"Miso Name 02", "Miso/name/2.png"},
        {"Miso Idle 01", "Miso/idle/1.png"},
        {"Miso Idle 02", "Miso/idle/2.png"},
        {"Miso Walking 01", "Miso/walking/1.png"},
        {"Miso Walking 02", "Miso/walking/2.png"},
        {"Miso Walking 03", "Miso/walking/3.png"},

        // Selection Screen
        {"Selection Arrow Off 01", "SelectionScreen/arrowOff01.png"},
        {"Selection Arrow Off 02", "SelectionScreen/arrowOff02.png"},
        {"Selection Arrow On 01", "SelectionScreen/arrowOn01.png"},
        {"Selection Arrow On 02", "SelectionScreen/arrowOn02.png"},
        {"Selection Frame 01", "SelectionScreen/frame01.png"},
        {"Selection Frame 02", "SelectionScreen/frame02.png"},

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
    // Main Menu
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
    
    // Instructions
    animationsManagerPtr->requestAnimation("Instructions", {
        { "Instructions 01", 500 },
        { "Instructions 02", 500 },
    });

    // Hammer Guy
    animationsManagerPtr->requestAnimation("Hammer Guy Jumping", {
        { "Hammer Guy Jumping 01", 500 },
        { "Hammer Guy Jumping 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Hammer Guy Name", {
        { "Hammer Guy Name 01", 500 },
        { "Hammer Guy Name 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Hammer Guy Idle", {
        { "Hammer Guy Idle 01", 700 },
        { "Hammer Guy Idle 02", 700 },
    });
    animationsManagerPtr->requestAnimation("Hammer Guy Walking", {
        { "Hammer Guy Walking 01", 500 },
        { "Hammer Guy Walking 02", 500 },
        { "Hammer Guy Walking 03", 500 },
    });
    animationsManagerPtr->requestAnimation("Hammer Guy Hit", {
        { "Hammer Guy Hit 01", 500 },
        { "Hammer Guy Hit 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Hammer Guy Ground", {
        { "Hammer Guy Ground 01", 700 },
        { "Hammer Guy Ground 02", 200 },
        { "Hammer Guy Ground 03", 700 },
    });
    animationsManagerPtr->requestAnimation("Hammer Guy Block", {
        { "Hammer Guy Block 01", 500 },
        { "Hammer Guy Block 02", 500 },
    });

    // Miso
    animationsManagerPtr->requestAnimation("Miso Jumping", {
        { "Miso Jumping 01", 500 },
        { "Miso Jumping 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Miso Name", {
        { "Miso Name 01", 500 },
        { "Miso Name 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Miso Idle", {
        { "Miso Idle 01", 500 },
        { "Miso Idle 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Miso Walking", {
        { "Miso Walking 01", 500 },
        { "Miso Walking 02", 500 },
        { "Miso Walking 03", 500 },
    });

    // Selection Screen
    animationsManagerPtr->requestAnimation("Selection Arrow On", {
        { "Selection Arrow On 01", 500 },
        { "Selection Arrow On 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Selection Arrow Off", {
        { "Selection Arrow Off 01", 500 },
        { "Selection Arrow Off 02", 500 },
        });
    animationsManagerPtr->requestAnimation("Selection Frame", {
        { "Selection Frame 01", 500 },
        { "Selection Frame 02", 500 },
    });

    // Beach background
    animationsManagerPtr->requestAnimation("Beach Background",{
        {"Beach Background 01", 500},
        {"Beach Background 02", 500},
        {"Beach Background 03", 500},
        {"Beach Background 04", 500},
        {"Beach Background 05", 500}
    });
}