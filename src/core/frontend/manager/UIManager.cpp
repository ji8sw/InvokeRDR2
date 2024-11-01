#include "UIManager.hpp"
#include "game/backend/ScriptMgr.hpp"
#include "game/backend/FiberPool.hpp"
#include "core/commands/Commands.hpp"

namespace YimMenu
{
	void UIManager::AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu)
	{
		if (!m_ActiveSubmenu)
			m_ActiveSubmenu = submenu;

		m_Submenus.push_back(std::move(submenu));
	}

	void UIManager::SetActiveSubmenuImpl(const std::shared_ptr<Submenu> Submenu)
	{
		m_ActiveSubmenu = Submenu;
	}

	void UIManager::DrawImpl()
	{
		auto pos = ImGui::GetCursorPos();

		if (ImGui::BeginChild("##submenus", ImVec2(120, ImGui::GetContentRegionAvail().y - 30), true))
		{
			for (auto& submenu : m_Submenus)
			{
				if (ImGui::Selectable(submenu->m_Name.data(), (submenu == m_ActiveSubmenu)))
				{
					SetActiveSubmenu(submenu);
				}
			}
		}
		ImGui::EndChild();
		
		if (ImGui::Button("Unload", ImVec2(120, 0)))
		{
			if (ScriptMgr::CanTick())
			{
				FiberPool::Push([] {
					Commands::Shutdown();
					g_Running = false;
				});
			}
			else
			{
				g_Running = false;
			}
		}

		pos.y -= 28;
		ImGui::SetCursorPos(ImVec2(pos.x + 130, pos.y));

		if (ImGui::BeginChild("##minisubmenus", ImVec2(0, 50), true, ImGuiWindowFlags_NoScrollbar))
		{
			if (m_ActiveSubmenu)
				m_ActiveSubmenu->DrawCategorySelectors();
		}
		ImGui::EndChild();

		ImGui::SetCursorPos(ImVec2(pos.x + 130, pos.y + 60));

		if (ImGui::BeginChild("##options", ImVec2(0, 0), true))
		{
			if (m_OptionsFont)
				ImGui::PushFont(m_OptionsFont);

			if (m_ActiveSubmenu)
				m_ActiveSubmenu->Draw();

			if (m_OptionsFont)
				ImGui::PopFont();
		}

		ImGui::EndChild();
	}

	std::shared_ptr<Submenu> UIManager::GetActiveSubmenuImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu;
		}

		return nullptr;
	}

	std::shared_ptr<Category> UIManager::GetActiveCategoryImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu->GetActiveCategory();
		}

		return nullptr;
	}
}
