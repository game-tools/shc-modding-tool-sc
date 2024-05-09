#include "ResourcesGui.h"
#include "../Market.h"
#include "../Bot/Character.h"
#include "../Config/Instances.h"
#include "../Bot/BotInstances.h"

#include "../imgui/imgui.h"

void resourcesGui::Render(std::map<DWORD, Player*> playerMap, DWORD selectedPlayerNumber) noexcept
{
	{
		ImGui::BeginChild("Child1", ImVec2(ImGui::GetContentRegionAvail().x * 0.65f, 400));
		if (ImGui::Button("Sell Resources"))
		{
			Market market;
			market.sell();
		}
		if (ImGui::Button("Add 10000 Gold"))
		{
			DWORD goldAddress = modBase + 0xd2b0b8 + 0x3124c + 0x39f4 * (selectedPlayerNumber + 1);
			*(DWORD*)goldAddress += 10000;
		}
		if (ImGui::Button("Add 20 Iron"))
		{
			playerMap[0]->mPlayerResources.Add(20, 6);
		}

		ImGui::EndChild();
	}

	ImGui::SameLine();

	{
		ImGui::BeginChild("Current Resources", ImVec2(ImGui::GetContentRegionAvail().x, 600));
		static ImGuiTableFlags resources_table_flags = 0;
		resources_table_flags |= ImGuiTableFlags_RowBg;
		resources_table_flags |= ImGuiTableFlags_Borders;
		resources_table_flags |= ImGuiTableFlags_SizingFixedFit;

		ImGui::SetWindowFontScale(1.2f);

		if (ImGui::BeginTable("Resources", 3, resources_table_flags))
		{
			ImGui::TableSetupColumn("Resource", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Count", ImGuiTableColumnFlags_WidthFixed, 50.0f);
			ImGui::TableSetupColumn("Actions");
			ImGui::TableHeadersRow();

			for (std::map<std::basic_string<TCHAR>, DWORD*>::iterator it = playerMap[selectedPlayerNumber]->mPlayerResources.mCurrentResourcesMap.begin(); it != playerMap[selectedPlayerNumber]->mPlayerResources.mCurrentResourcesMap.end(); it++) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(it->first.c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%d", *(it->second));
				ImGui::TableSetColumnIndex(2);
				ImGui::PushID(Config::pResourcesConfig->m_ids_map[it->first]);
				if (ImGui::Button("Add 20")) {
					playerMap[selectedPlayerNumber]->mPlayerResources.Add(20, Config::pResourcesConfig->m_ids_map[it->first]);
				}
				ImGui::SameLine();
				if (ImGui::Button("Enqueue 50")) {
					*(playerMap[selectedPlayerNumber]->mPlayerResources.mEnqueuedResourcesMap[it->first]) += 50;
				}
				ImGui::PopID();

			}
			ImGui::EndTable();
		}
		ImGui::EndChild();
	}
}