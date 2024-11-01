#include "Trolling.hpp"

#include "game/backend/FiberPool.hpp"
#include "game/rdr/Natives.hpp"
#include "game/frontend/submenus/Players.hpp"
#include "game/backend/Players.hpp"

namespace YimMenu::Submenus
{	
	std::shared_ptr<Category> BuildTrollingMenu()
	{
		auto menu = std::make_shared<Category>("Trolling");
		menu->AddItem(std::make_shared<PlayerCommandItem>("cageplayersmall"_J));
		menu->AddItem(std::make_shared<PlayerCommandItem>("cageplayerlarge"_J));
		menu->AddItem(std::make_shared<PlayerCommandItem>("cageplayercircus"_J));

		auto attachments = std::make_shared<Group>("Attachments");
		attachments->AddItem(std::make_shared<PlayerCommandItem>("spank"_J));
		attachments->AddItem(std::make_shared<PlayerCommandItem>("rideonshoulders"_J));
		attachments->AddItem(std::make_shared<PlayerCommandItem>("touchplayer"_J));
		attachments->AddItem(std::make_shared<PlayerCommandItem>("slap"_J));
		attachments->AddItem(std::make_shared<CommandItem>("cancelattachment"_J));
		menu->AddItem(attachments);

		auto Law = std::make_shared<Group>("Law");
		Law->AddItem(std::make_shared<ImGuiItem>([] {
			if (ImGui::Button("Kick from horse"))
			{
				FiberPool::Push([] 
				{
					if (YimMenu::Players::GetSelected().GetPed())
						YimMenu::Players::GetSelected().GetPed().KickFromMount();
				});
			}
		}));

		menu->AddItem(Law);

		return menu;
	}
}