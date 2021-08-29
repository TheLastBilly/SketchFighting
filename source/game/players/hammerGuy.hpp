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

			entities::player* createPlayer(const std::string &name) override
			{
				entities::player *player = new entities::player(
					name,

					animationsManager->getAnimation("Hammer Guy Idle"),
					animationsManager->getAnimation("Hammer Guy Walking"),
					animationsManager->getAnimation("Hammer Guy Jumping"),

					animationsManager->getAnimation("Hammer Guy Hit"),
					animationsManager->getAnimation("Hammer Guy Block"),
					animationsManager->getAnimation("Hammer Guy Ground")
				);
			
				player->setGravity(.02);
				player->setHorizontalSpeed(.3);
				player->setJumpSpeed(10.);

				player->setSpritesSize(300,300);

				return player;
			}

			graphics::animation* getIntroAnimation() override
			{
				graphics::animation* intro = animationsManager->getAnimation("Hammer Guy Idle");
				intro->setSpritesSize(350,350);
				return intro;
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Hammer Guy Name");
			}
		};
	}
}