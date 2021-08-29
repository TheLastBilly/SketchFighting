#pragma once

#include "maps/genericBackground.hpp"

namespace ksf
{
	namespace maps
	{
		class theboard: public genericBackground
		{
		public:
			theboard(engine::managers::animationsManager* animationsManager) : genericBackground("The Board", animationsManager) {}

			graphics::animation* getBackground() override
			{
				return animationsManager->getAnimation("The Board");
			}

			graphics::animation* getIntroAnimation() override
			{
				graphics::animation* intro = animationsManager->getAnimation("The Board");
				intro->setSpritesSize(400, 400);
				return intro;
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("The Board Name");
			}

			int getFloorHeight() override
			{
				return 10;
			}
		};
	}
}