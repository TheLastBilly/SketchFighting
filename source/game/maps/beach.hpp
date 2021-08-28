#pragma once

#include "maps/genericBackground.hpp"

namespace ksf
{
	namespace maps
	{
		class beach: public genericBackground
		{
		public:
			beach(engine::managers::animationsManager* animationsManager) : genericBackground("Beach", animationsManager) {}

			graphics::animation* getBackground() override
			{
				return animationsManager->getAnimation("Beach Background");
			}

			graphics::animation* getIntroAnimation() override
			{
				graphics::animation* intro = animationsManager->getAnimation("Beach Background");
				intro->setSpritesSize(300, 300);
				return intro;
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Hammer Guy Name");
			}

			int getFloorHeight() override
			{
				return 10;
			}
		};
	}
}