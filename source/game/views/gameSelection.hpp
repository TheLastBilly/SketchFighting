#pragma once

#include "engine/managers/animationsManager.hpp"
#include "engine/managers/viewsManager.hpp"
#include "engine/managers/nodesManager.hpp"

#include "graphics/view.hpp"
#include "graphics/animation.hpp"

#include "entities/player.hpp"
#include "entities/globalSettings.hpp"

#include "players/hammerGuy.hpp"
#include "players/miso.hpp"
#include "players/uero.hpp"

#include "maps/beach.hpp"

namespace ksf
{
	namespace views
	{
		class gameSelection : public graphics::view
		{
		public:
			gameSelection() : view("Game Selection") {}

			void setup() override;
			void update(size_t delta) override;
			void cleannup() override;
			
			inline void decrementOption()
			{ option = option < 1 ? options - 1 : option - 1; }
			inline void incrementOption()
			{ option = option >= options -1 ? 0 : option+1; }

		protected:
			void initialize() override;

		private:
			engine::managers::animationsManager* animationsManager = nullptr;
			engine::managers::viewsManager* viewsManager = nullptr;
			engine::managers::nodesManager* nodesManager = nullptr;
			engine::keyboardHandler* keyboardHandler = nullptr;

			entities::player::controller player1Controller, player2Controller;
            entities::player::controller* currentController = nullptr;

            entities::globalSettings* globalSettings = nullptr;

			engine::entity
				* selectionFrame = nullptr, 
				* selectionArrow = nullptr,
				* playerName = nullptr,
                * currentSelection = nullptr;
            
            graphics::animation  
                *selectionOn = nullptr, 
                *selectionOff = nullptr,
                
                *leftArrowAnimation = nullptr,
                *rightArrowAnimation = nullptr,
                
                *currentAnimation = nullptr;

			int option = 0, options = 0, playerCount = 0;
			bool playersSelected = false, buttonPressed = false;

			int selectDelay = 500;

			size_t counter = 0;

        private:
			std::vector<players::genericPlayer*> players;
			std::vector<maps::genericBackground*> maps;
		};
	}
}