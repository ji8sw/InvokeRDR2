#pragma once
#include "game/features/Features.hpp"
#include "game/frontend/submenus/commands/PlayerCommand.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/rdr/Enums.hpp"
#include "game/rdr/Natives.hpp"

namespace YimMenu::Features
{
	class SlipOver : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{ 
			int ped = PLAYER::GET_PLAYER_PED(player.GetId());
			if (ped != 0)
			{
				PED::SET_PED_TO_RAGDOLL(ped, 1000, 5000, 0, 0, 0, 0);
			}
		}
	};

	static SlipOver _SlipOver{"slipover", "Slip Over", "Forces the player to trip over"};
}