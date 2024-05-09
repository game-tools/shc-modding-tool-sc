#include "UnitsGui.h"
#include "../Unit.h"
#include "../Config/Instances.h"

#include "../imgui/imgui.h"

void unitsGui::Render(std::map<DWORD, Player*> playerMap, DWORD selectedPlayerNumber) noexcept
{
	{
		ImGui::BeginChild("UnitsGui", ImVec2(ImGui::GetContentRegionAvail().x * 0.7f, 400));
		if (ImGui::Button("Train Horse Archers"))
		{
			Unit unit;
			unit.recruit("3");
		}
		ImGui::EndChild();
	}

	ImGui::SameLine();

	{
		ImGui::BeginChild("Current Units", ImVec2(ImGui::GetContentRegionAvail().x, 600));
		static ImGuiTableFlags units_table_flags = 0;
		units_table_flags |= ImGuiTableFlags_RowBg;
		units_table_flags |= ImGuiTableFlags_Borders;
		units_table_flags |= ImGuiTableFlags_SizingFixedFit;

		ImGui::SetWindowFontScale(1.2f);

		if (ImGui::BeginTable("Units", 3, units_table_flags))
		{
			ImGui::TableSetupColumn("Unit", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Count", ImGuiTableColumnFlags_WidthFixed, 50.0f);
			ImGui::TableSetupColumn("Actions");
			ImGui::TableHeadersRow();

			for (std::map<std::basic_string<TCHAR>, DWORD*>::iterator it = playerMap[selectedPlayerNumber]->mPlayerUnits.mCurrentEuropeanUnitsMap.begin(); it != playerMap[selectedPlayerNumber]->mPlayerUnits.mCurrentEuropeanUnitsMap.end(); it++) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(it->first.c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%d", *(it->second));
				ImGui::TableSetColumnIndex(2);
				ImGui::PushID(Config::pUnitsConfig->mData["units"][it->first]);
				if (ImGui::Button("Recruit 20")) {
					playerMap[selectedPlayerNumber]->mPlayerUnits.Recruit(Config::pUnitsConfig->mData["units"][it->first], 20);
				}
				ImGui::PopID();

			}

			for (std::map<std::basic_string<TCHAR>, DWORD*>::iterator it = playerMap[selectedPlayerNumber]->mPlayerUnits.mCurrentArabianUnitsMap.begin(); it != playerMap[selectedPlayerNumber]->mPlayerUnits.mCurrentArabianUnitsMap.end(); it++) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(it->first.c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("Unknown");
				ImGui::TableSetColumnIndex(2);
				ImGui::PushID(Config::pUnitsConfig->mData["units"][it->first]);
				if (ImGui::Button("Recruit 20")) {
					playerMap[selectedPlayerNumber]->mPlayerUnits.Recruit(Config::pUnitsConfig->mData["units"][it->first], 20);
				}
				ImGui::PopID();

			}
			ImGui::EndTable();
		}
		ImGui::EndChild();
	}
}