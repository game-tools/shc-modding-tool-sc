#include <windows.h>
#include <string>

#include "AutomationsGui.h"
#include "../Globals.h"
#include "../Config/Instances.h"
#include "../Automations/AutomationsInstances.h"

#include "../imgui/imgui.h"

void automationsGui::Render() noexcept {
	{
		ImGui::BeginChild("Units Cost", ImVec2(ImGui::GetContentRegionAvail().x * 0.4f, 800));

		static bool autoSelling = market->mAutoSelling;
		ImGui::Checkbox("Auto Selling", &market->mAutoSelling);

		if (market->mAutoSelling != autoSelling) {
			autoSelling = market->mAutoSelling;
			market->mCurrentResourcesTimer = 0;
		}

		DWORD step = 1;

		ImGui::SameLine();
		ImGui::PushItemWidth(150.0f);
		ImGui::InputScalar("Selling Interval", ImGuiDataType_U32, &(Automations::pMarketAutomations->mSellResourcesInterval), &step, NULL, "%u");
		ImGui::PopItemWidth();

		static ImGuiTableFlags resourceSellingTableflags = 0;
		resourceSellingTableflags |= ImGuiTableFlags_RowBg;
		resourceSellingTableflags |= ImGuiTableFlags_Borders;
		resourceSellingTableflags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("Resource Selling", 3, resourceSellingTableflags))
		{
			ImGui::TableSetupColumn("Resource", ImGuiTableColumnFlags_WidthFixed, 120.0f);
			ImGui::TableSetupColumn("Sell Threshold", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Sell (1 - Yes, 0 - No)", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableHeadersRow();

			byte i = 0;
			while (Automations::resourceNames[i] != NULL) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(Automations::resourceNames[i]);
				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(i * 2);
				ImGui::InputScalar(Automations::resourceNames[i], ImGuiDataType_U32, &(Automations::pMarketAutomations->mAutoSelling[i * 2]), &step, NULL, "%u");
				ImGui::PopID();
				ImGui::TableSetColumnIndex(2);
				ImGui::PushID((i + 1) * 2);
				ImGui::InputScalar(Automations::resourceNames[i], ImGuiDataType_U8, &(Automations::pMarketAutomations->mAutoSelling[i * 2 + 1]), &step, NULL, "%u");
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
		ImGui::Text(Config::pMarketConfig->mDefaultName.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Selected")) {
			Config::pMarketConfig->Load(Config::pMarketConfig->savedConfigNames[selected]);
			Automations::pMarketAutomations->LoadConfig();
		}

		if (ImGui::Button("Save")) {
			Automations::pMarketAutomations->PrepareConfig();
			Config::pMarketConfig->Save((std::string)buf);
		}

		ImGui::SameLine();

		if (ImGui::Button("Save as Default")) {
			Automations::pMarketAutomations->PrepareConfig();
			Config::pMarketConfig->SaveDefault((std::string)buf);
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Selected")) {
			Config::pMarketConfig->Delete(Config::pMarketConfig->savedConfigNames[selected]);
		}

		ImGui::SameLine();

		if (ImGui::Button("Remove Default")) {
			Config::pMarketConfig->RemoveDefault();
		}

		ImGui::InputText("Save file name", buf, 64, ImGuiInputTextFlags_CharsNoBlank);

		byte n = 0;
		for (std::basic_string<TCHAR> configFileName : Config::pMarketConfig->savedConfigNames) {
			if (ImGui::Selectable(configFileName.c_str(), selected == n))
				selected = n;
			n++;
		}

		ImGui::EndChild();
	}
}