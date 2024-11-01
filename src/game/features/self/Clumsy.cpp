#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/rdr/Natives.hpp"

namespace YimMenu::Features
{
	class Clumsy : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPed())
				PED::SET_PED_RAGDOLL_ON_COLLISION(Self::GetPed().GetHandle(), true, true);
		}

        virtual void OnDisable() override
        {
			if (Self::GetPed())
				PED::SET_PED_RAGDOLL_ON_COLLISION(Self::GetPed().GetHandle(), false, false);
        }
	};

	static Clumsy _Clumsy("clumsy", "Clumsy", "Makes you trip over when you bump into things");
}