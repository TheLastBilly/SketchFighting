#pragma once

#include "players/genericPlayer.hpp"

namespace ksf
{
	namespace players
	{
		class uero: public genericPlayer
		{
		private:
			class ueroPlayer : public entities::player
			{
			public:
				ueroPlayer(
					const std::string& name,
					graphics::animation* idleAnimation,
					graphics::animation* walkingAnimation,
					graphics::animation* jumpingAnimation,
					graphics::animation* hitAnimation,
					graphics::animation* blockAnimation,
					graphics::animation* attackAnimation
				) : player(name, idleAnimation, walkingAnimation, jumpingAnimation, hitAnimation, blockAnimation, attackAnimation) {}

				void flipToTheRight() override
				{
					getCurrentAnimation()->flipSprites(graphics::sprite::flip::none);
				}
				void flipToTheLeft() override
				{
					getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);
				}
			};

		public:
			uero(engine::managers::animationsManager* animationsManager) : genericPlayer("Uero", animationsManager) {}

			entities::player* createPlayer(const std::string &name) override
			{
				entities::player *player = new ueroPlayer(
					name,

					animationsManager->getAnimation("Uero Idle"),
					animationsManager->getAnimation("Uero Walking"),
					animationsManager->getAnimation("Uero Jumping"),

					animationsManager->getAnimation("Uero Hit"),
					animationsManager->getAnimation("Uero Block"),
					animationsManager->getAnimation("Uero Ground")
				);
			
				player->setGravity(.02);
				player->setHorizontalSpeed(.3);
				player->setJumpSpeed(10.);

				player->setSpritesSize(250,250);

				return player;
			}

			graphics::animation* getIntroAnimation() override
			{
				graphics::animation* intro = animationsManager->getAnimation("Uero Idle");
				intro->setSpritesSize(350,350);
				return intro;
			}
			graphics::animation* getNameAnimation()
			{
				return animationsManager->getAnimation("Uero Name");
			}
		};
	}
}