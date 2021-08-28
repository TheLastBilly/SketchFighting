#pragma once

#include "engine/managers/animationsManager.hpp"
#include "engine/managers/viewsManager.hpp"
#include "engine/managers/nodesManager.hpp"

#include "graphics/view.hpp"
#include "graphics/animation.hpp"

#include "entities/player.hpp"
#include "entities/globalSettings.hpp"

namespace ksf
{
	namespace views
	{
		class mainMenu: public graphics::view
		{
		public:
			mainMenu() : view("Main Menu") {}

			void setup() override;
			void update(size_t delta) override;
			void cleannup() override;

		protected:
			void initialize() override;

		private:
			engine::managers::animationsManager* animationsManager = nullptr;
			engine::managers::viewsManager* viewsManager = nullptr;
			engine::managers::nodesManager* nodesManager = nullptr;
			engine::keyboardHandler* keyboardHandler = nullptr;

			engine::entity
				* title = nullptr,
				* quit = nullptr,
				* play = nullptr,
				* arrow = nullptr;
			
			graphics::animation
				* arrowOn = nullptr,
				* arrowOff = nullptr;
			
			int option = 0;
			bool optionSelected = false;

			int selectDelay = 1000;
		};
	}
}