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
		class fadingView : public graphics::view
		{
		public:
			fadingView(const std::string &name, const std::string &animationName, size_t width, size_t height, size_t duration, const std::string &nextSceneName):
				view(name),
				animationName(animationName),
				width(width),
				height(height),
				duration(duration),
				nextSceneName(nextSceneName)
			{}

			void setup() override;
			void update(size_t delta) override;
			void cleannup() override;

		protected:
			void initialize() override;

		private:
			engine::managers::animationsManager* animationsManager = nullptr;
			engine::managers::viewsManager* viewsManager = nullptr;

			graphics::animation *animationPtr = nullptr;

			size_t counter = 0;
			int alpha = 0;

			const std::string animationName, nextSceneName;
			const size_t fadeDelay = 4000, fadeStep = fadeDelay /255;
			const size_t duration, width, height;
		};
	}
}