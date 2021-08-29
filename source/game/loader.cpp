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

        // Uero
        {"Uero Jumping 01", "Uero/jumping01.png"},
        {"Uero Jumping 02", "Uero/jumping02.png"},
        {"Uero Name 01", "Uero/name01.png"},
        {"Uero Name 02", "Uero/name02.png"},
        {"Uero Idle 01", "Uero/idle01.png"},
        {"Uero Idle 02", "Uero/idle02.png"},
        {"Uero Walking 01", "Uero/walking01.png"},
        {"Uero Walking 02", "Uero/walking02.png"},
        {"Uero Block 01", "Uero/block01.png"},
        {"Uero Hit 01", "Uero/hit01.png"},
        {"Uero Hit 02", "Uero/hit02.png"},
        {"Uero Hit 03", "Uero/hit03.png"},

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

        // UI
        {"UI Pencil Ok 01", "ui/pencilOk01.png"},
        {"UI Pencil Ok 02", "ui/pencilOk02.png"},
        {"UI Pencil Bad 01", "ui/pencilBad01.png"},
        {"UI Pencil Bad 02", "ui/pencilBad02.png"},
        {"UI Circle 01", "ui/circle01.png"},
        {"UI Circle 02", "ui/circle02.png"},
        {"UI P1 01", "ui/p101.png"},
        {"UI P1 02", "ui/p102.png"},
        {"UI P2 01", "ui/p201.png"},
        {"UI P2 02", "ui/p202.png"},
        {"UI P1 Wins 01", "ui/p1wins01.png"},
        {"UI P1 Wins 02", "ui/p1wins02.png"},
        {"UI P2 Wins 01", "ui/p2wins01.png"},
        {"UI P2 Wins 02", "ui/p2wins02.png"},

        // Beach background
        {"Beach Background 01", "beach/1.png"},
        {"Beach Background 02", "beach/2.png"},
        {"Beach Background 03", "beach/3.png"},
        {"Beach Background 04", "beach/4.png"},
        {"Beach Background 05", "beach/5.png"},

        // Credits
        {"Credits 01", "Credits/1.png"},
        {"Credits 02", "Credits/2.png"},
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

    // Uero
    animationsManagerPtr->requestAnimation("Uero Jumping", {
        { "Uero Jumping 01", 500 },
        { "Uero Jumping 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Uero Name", {
        { "Uero Name 01", 500 },
        { "Uero Name 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Uero Idle", {
        { "Uero Idle 01", 700 },
        { "Uero Idle 02", 700 },
    });
    animationsManagerPtr->requestAnimation("Uero Walking", {
        { "Uero Walking 01", 500 },
        { "Uero Walking 02", 500 },
    });
    animationsManagerPtr->requestAnimation("Uero Hit", {
        { "Uero Block 01", 500 },
    });
    animationsManagerPtr->requestAnimation("Uero Ground", {
        { "Uero Hit 01", 700 },
        { "Uero Hit 02", 200 },
    });
    animationsManagerPtr->requestAnimation("Uero Block", {
        { "Uero Block 01", 500 },
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

    // UI
    animationsManagerPtr->requestAnimation("UI Pencil Ok", {
        { "UI Pencil Ok 01", 500 },
        { "UI Pencil Ok 02", 500 },
    });
    animationsManagerPtr->requestAnimation("UI Pencil Bad", {
        { "UI Pencil Bad 01", 500 },
        { "UI Pencil Bad 02", 500 },
    });
    animationsManagerPtr->requestAnimation("UI Circle", {
        { "UI Circle 01", 500 },
        { "UI Circle 02", 500 },
    });
    animationsManagerPtr->requestAnimation("UI P1", {
        { "UI P1 01", 500 },
        { "UI P1 02", 500 },
    });
    animationsManagerPtr->requestAnimation("UI P2", {
        { "UI P2 01", 500 },
        { "UI P2 02", 500 },
    });
    animationsManagerPtr->requestAnimation("UI P1 Wins", {
        { "UI P1 Wins 01", 500 },
        { "UI P1 Wins 02", 500 },
    });
    animationsManagerPtr->requestAnimation("UI P2 Wins", {
        { "UI P2 Wins 01", 500 },
        { "UI P2 Wins 02", 500 },
    });


    // Credits
    animationsManagerPtr->requestAnimation("Credits", {
        { "Credits 01", 500 },
        { "Credits 02", 500 },
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