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
		class instructions : public graphics::view
		{
		public:
			instructions() : view("Instructions") {}

			void setup() override;
			void update(size_t delta) override;
			void cleannup() override;

		protected:
			void initialize() override;

		private:
			engine::managers::animationsManager* animationsManager = nullptr;
			engine::managers::viewsManager* viewsManager = nullptr;

			graphics::animation *instructionsPtr = nullptr;

			size_t counter = 0;
			int alpha = 0;

			const size_t showDelay = 5000, fadeDelay = 4000, fadeStep = fadeDelay /255;
		};
	}
}