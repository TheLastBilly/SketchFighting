#pragma once

#include "utilities/loader.hpp"

namespace ksf
{
	namespace players
	{
		class hammerGuy: public utilities::playerLoader
		{
			entities::player* loadPlayer(const std::string &name, engine::managers::animationsManager* animationsManager) override
			{
				entities::player *player = new entities::player(
					name,

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
		};
	}
}