#pragma once

#include "players/genericPlayer.hpp"

namespace ksf
{
	namespace players
	{
		class miso: public genericPlayer
		{
		public:
			miso(engine::managers::animationsManager* animationsManager) : genericPlayer("Miso", animationsManager) {}

			entities::player* createPlayer() override
			{
				entities::player *player = new entities::player(
					getName(),

					animationsManager->getAnimation("Miso Idle"),
					animationsManager->getAnimation("Miso Walking"),
					animationsManager->getAnimation("Miso Jumping")
				);

				player->setGravity(.02);
				player->setHorizontalSpeed(.3);
				player->setJumpSpeed(10.);

				player->setSpritesSize(200,200);

				return player;
			}

			graphics::animation* getIdleAnimation() override
			{
				return animationsManager->getAnimation("Miso Idle");
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Miso Name");
			}
		};
	}
}