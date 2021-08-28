#pragma once

#include "players/genericPlayer.hpp"

namespace ksf
{
	namespace players
	{
		class hammerGuy: public genericPlayer
		{
		public:
			hammerGuy(engine::managers::animationsManager* animationsManager) : genericPlayer("Hammer Guy", animationsManager) {}

			entities::player* createPlayer() override
			{
				entities::player *player = new entities::player(
					getName(),

					animationsManager->getAnimation("Hammer Guy Idle"),
					animationsManager->getAnimation("Hammer Guy Walking"),
					animationsManager->getAnimation("Hammer Guy Jumping")
				);

				player->setGravity(.02);
				player->setHorizontalSpeed(.3);
				player->setJumpSpeed(10.);

				player->setSpritesSize(200,200);

				return player;
			}

			graphics::animation* getIdleAnimation() override
			{
				return animationsManager->getAnimation("Hammer Guy Idle");
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Hammer Guy Name");
			}
		};
	}
}