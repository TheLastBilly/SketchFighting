#pragma once

#include "engine/node.hpp"

#include "entities/player.hpp"
#include "views/map.hpp"

namespace ksf
{
	namespace entities
	{
		class globalSettings : public engine::node
		{
		public:
			globalSettings() : node("Global Settings") {}

			entities::player* player1 = nullptr, * player2 = nullptr;
			views::map::background *background = nullptr;
			int floorHeight = 0;

			entities::player::controller player1Controller, player2Controller;
		};
	}
}