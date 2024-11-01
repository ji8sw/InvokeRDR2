#include "game/features/Features.hpp"
#include "game/frontend/submenus/commands/PlayerCommand.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/rdr/Enums.hpp"
#include "game/rdr/Natives.hpp"

namespace YimMenu::Features
{
	class SetWantedScoreMax : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{ 
			LAW::SET_WANTED_SCORE(player.GetId(), 5);
		}
	};

	class SetWantedScoreMin : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{ 
			LAW::SET_WANTED_SCORE(player.GetId(), 0);
		}
	};

	static SetWantedScoreMax _SetWantedScoreMax{"setwantedscoremax", "Set Wanted Score Max", "Sets the players wanted score to maximum"};
	static SetWantedScoreMin _SetWantedScoreMin{"setwantedscoremin", "Set Wanted Score Min", "Sets the players wanted score to minimum"};
}