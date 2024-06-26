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

			entities::player* createPlayer(const std::string& name) override
			{
				entities::player *player = new entities::player(
					name,

					animationsManager->getAnimation("Miso Idle"),
					animationsManager->getAnimation("Miso Walking"),
					animationsManager->getAnimation("Miso Jumping"),
					animationsManager->getAnimation("Miso Jumping"),
					animationsManager->getAnimation("Miso Jumping"),
					animationsManager->getAnimation("Miso Jumping")
				);

				player->setGravity(.02);
				player->setHorizontalSpeed(.3);
				player->setJumpSpeed(10.);

				player->setSpritesSize(300,300);

				return player;
			}

			graphics::animation* getIntroAnimation() override
			{
				graphics::animation* intro = animationsManager->getAnimation("Miso Idle");
				intro->setSpritesSize(450,450);
				return intro;
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Miso Name");
			}
		};
	}
}