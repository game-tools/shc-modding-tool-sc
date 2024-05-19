#include <windows.h>
#include <string>

#include "UnitPropertiesGui.h"
#include "../Units/UnitsInstances.h"
#include "../Config/Instances.h"

#include "../imgui/imgui.h"

void unitPropertiesGui::Render() noexcept {
	static ImGuiTableFlags unitPropertiesTableFlags = 0;
	unitPropertiesTableFlags |= ImGuiTableFlags_RowBg;
	unitPropertiesTableFlags |= ImGuiTableFlags_Borders;
	unitPropertiesTableFlags |= ImGuiTableFlags_SizingFixedFit;
	unitPropertiesTableFlags |= ImGuiTableFlags_ScrollX;

	const float textBaseHeight = ImGui::GetTextLineHeightWithSpacing();
	ImVec2 size = ImVec2(0.0f, textBaseHeight * 39);
	if (ImGui::BeginTable("Unit Properties", 20, unitPropertiesTableFlags, size))
	{
		ImGui::TableSetupColumn("Unit Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
		ImGui::TableSetupColumn("HP", ImGuiTableColumnFlags_WidthFixed, 150.0f);
		int i = 0;
		while (Units::damageLabels[i] != NULL) {
			ImGui::TableSetupColumn(Units::damageLabels[i], ImGuiTableColumnFlags_WidthFixed, 150.0f);
			i++;
		}
		ImGui::TableHeadersRow();

		DWORD step = 1;

		i = 0;
		while (Units::nameLabels[i] != NULL) {
			if (Units::nameLabels[i] != "NULL") {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(Units::nameLabels[i]);
				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(i);
				ImGui::InputScalar(Units::nameLabels[i], ImGuiDataType_U32, &(Units::pUnitHps->u1) + i, &step, NULL, "%u");
				ImGui::PopID();

				byte i2 = 0;
				while (Units::damageLabels[i2] != NULL) {
					ImGui::TableSetColumnIndex(i2+2);
					ImGui::PushID(i2+2);
					ImGui::InputScalar(Units::nameLabels[i], ImGuiDataType_U32, &(Units::pUnitDamage[i2]->u1) + i, &step, NULL, "%u");
					ImGui::PopID();
					i2++;
				}
			}
			i++;
		}

		ImGui::EndTable();
	}

	ImGui::Text("Columns are Attack Types; Rows are targets (HP is just HP). Example: Arab Archer does 3000 ranged damage to siege tower and 10 melee damage to siege tower");

	ImGui::SeparatorText("Config");

	static int selected = -1;
	static char buf[64] = "";

	ImGui::Text("Default config:");
	ImGui::SameLine();
	ImGui::Text(Config::pUnitPropertiesConfig->mDefaultName.c_str());
	ImGui::SameLine();

	if (ImGui::Button("Load")) {
		Config::pUnitPropertiesConfig->Load(Config::pUnitPropertiesConfig->savedConfigNames[selected]);
		Units::LoadConfig();
	}

	if (ImGui::Button("Save")) {
		Units::PrepareConfig();
		Config::pUnitPropertiesConfig->Save((std::string)buf);
	}

	ImGui::SameLine();

	if (ImGui::Button("Save as Default")) {
		Units::PrepareConfig();
		Config::pUnitPropertiesConfig->SaveDefault((std::string)buf);
	}

	ImGui::SameLine();

	if (ImGui::Button("Delete Selected")) {
		Config::pUnitPropertiesConfig->Delete(Config::pUnitPropertiesConfig->savedConfigNames[selected]);
	}

	ImGui::SameLine();

	if (ImGui::Button("Remove Default")) {
		Config::pUnitPropertiesConfig->RemoveDefault();
	}

	ImGui::InputText("Save file name", buf, 64, ImGuiInputTextFlags_CharsNoBlank);

	byte n = 0;
	for (std::basic_string<TCHAR> configFileName : Config::pUnitPropertiesConfig->savedConfigNames) {
		if (ImGui::Selectable(configFileName.c_str(), selected == n))
			selected = n;
		n++;
	}
}