#pragma once

#include "players/genericPlayer.hpp"

namespace ksf
{
	namespace players
	{
		class doggi: public genericPlayer
		{
		public:
			doggi(engine::managers::animationsManager* animationsManager) : genericPlayer("Doggi", animationsManager) {}

			entities::player* createPlayer(const std::string& name) override
			{
				entities::player *player = new entities::player(
					name,

					animationsManager->getAnimation("Doggi Idle"),
					animationsManager->getAnimation("Doggi Idle"),
					animationsManager->getAnimation("Doggi Jumping"),
					animationsManager->getAnimation("Doggi Hit"),
					animationsManager->getAnimation("Doggi Idle"),
					animationsManager->getAnimation("Doggi Attack")
				);

				player->setGravity(.02);
				player->setHorizontalSpeed(.3);
				player->setJumpSpeed(10.);

				player->setSpritesSize(200,200);

				return player;
			}

			graphics::animation* getIntroAnimation() override
			{
				graphics::animation* intro = animationsManager->getAnimation("Doggi Idle");
				intro->setSpritesSize(450,450);
				return intro;
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Doggi Name");
			}
		};
	}
}