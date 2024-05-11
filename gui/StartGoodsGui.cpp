#include "StartGoodsGui.h"
#include "../Start/StartInstances.h"
#include "../Config/Instances.h"

#include "../imgui/imgui.h"

void startGoodsGui::Render() noexcept {
	{
		ImGui::BeginChild("Child1", ImVec2(ImGui::GetContentRegionAvail().x * 0.6f, 600));

		static ImGuiTableFlags startResourcesTableFlags = 0;
		startResourcesTableFlags |= ImGuiTableFlags_RowBg;
		startResourcesTableFlags |= ImGuiTableFlags_Borders;
		startResourcesTableFlags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("Start Resources", 4, startResourcesTableFlags))
		{
			ImGui::TableSetupColumn("Resource", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Normal", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Crusade", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Skirmish", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableHeadersRow();

			DWORD step = 1;

			int i = 0;
			while (Start::startResourcesLabels[i] != NULL) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(Start::startResourcesLabels[i]);
				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(i);
				ImGui::InputScalar(Start::startResourcesLabels[i], ImGuiDataType_U32, &(Start::startResources[0]->wood) + i, &step, NULL, "%u");
				ImGui::PopID();
				ImGui::TableSetColumnIndex(2);
				ImGui::PushID(i + 1);
				ImGui::InputScalar(Start::startResourcesLabels[i], ImGuiDataType_U32, &(Start::startResources[1]->wood) + i, &step, NULL, "%u");
				ImGui::PopID();
				ImGui::TableSetColumnIndex(3);
				ImGui::PushID(i + 2);
				ImGui::InputScalar(Start::startResourcesLabels[i], ImGuiDataType_U32, &(Start::startResources[2]->wood) + i, &step, NULL, "%u");
				ImGui::PopID();

				i++;
			}
			ImGui::EndTable();
		}

		ImGui::EndChild();
	}

	ImGui::SameLine();

	{
		ImGui::BeginChild("Child2", ImVec2(ImGui::GetContentRegionAvail().x, 600));

		static ImGuiTableFlags startGoldTableFlags = 0;
		startGoldTableFlags |= ImGuiTableFlags_RowBg;
		startGoldTableFlags |= ImGuiTableFlags_Borders;
		startGoldTableFlags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("Start Gold", 3, startGoldTableFlags))
		{
			ImGui::TableSetupColumn("Mode", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Player", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("AI", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableHeadersRow();

			DWORD step = 1;

			int i = 0;
			while (Start::startGoldLabels[i] != NULL) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(Start::startGoldLabels[i]);
				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(i);
				ImGui::InputScalar(Start::startGoldLabels[i], ImGuiDataType_U32, &(Start::startGold->gold1) + i * 2, &step, NULL, "%u");
				ImGui::PopID();
				ImGui::TableSetColumnIndex(2);
				ImGui::PushID(i + 1);
				ImGui::InputScalar(Start::startGoldLabels[i], ImGuiDataType_U32, &(Start::startGold->gold2) + i * 2, &step, NULL, "%u");
				ImGui::PopID();

				i++;
			}
			ImGui::EndTable();
		}

		ImGui::SeparatorText("Config");

		static int selected = -1;
		static char buf[64] = "";

		ImGui::Text("Default config:");
		ImGui::SameLine();
		ImGui::Text(Config::pStartGoodsConfig->mDefaultName.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Selected")) {
			Config::pStartGoodsConfig->Load(Config::pStartGoodsConfig->savedConfigNames[selected]);
			Start::LoadGoodsConfig();
		}

		if (ImGui::Button("Save")) {
			Start::PrepareGoodsConfig();
			Config::pStartGoodsConfig->Save((std::string)buf);
		}

		ImGui::SameLine();

		if (ImGui::Button("Save as Default")) {
			Start::PrepareGoodsConfig();
			Config::pStartGoodsConfig->SaveDefault((std::string)buf);
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Selected")) {
			Config::pStartGoodsConfig->Delete(Config::pStartGoodsConfig->savedConfigNames[selected]);
		}

		ImGui::SameLine();

		if (ImGui::Button("Remove Default")) {
			Config::pStartGoodsConfig->RemoveDefault();
		}

		ImGui::InputText("Save file name", buf, 64, ImGuiInputTextFlags_CharsNoBlank);

		byte n = 0;
		for (std::basic_string<TCHAR> configFileName : Config::pStartGoodsConfig->savedConfigNames) {
			if (ImGui::Selectable(configFileName.c_str(), selected == n))
				selected = n;
			n++;
		}

		ImGui::EndChild();
	}
}