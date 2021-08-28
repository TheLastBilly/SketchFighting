#pragma once

#include "engine/node.hpp"

#include "entities/player.hpp"

namespace ksf
{
	namespace entities
	{
		class globalSettings : public engine::node
		{
		public:
			globalSettings() : node("Global Settings") {}

			player* player1 = nullptr, * player2 = nullptr;
			graphics::animation *background = nullptr;
			int floorHeight = 0;

			entities::player::controller player1Controller, player2Controller;
		};
	}
}