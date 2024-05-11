#include <map>
#include <windows.h>
#include <string>

#include "PricesGui.h"
#include "../Globals.h"
#include "../Config/Instances.h"

#include "../imgui/imgui.h"

void pricesGui::Render() noexcept {
	{
		ImGui::BeginChild("Units Cost", ImVec2(ImGui::GetContentRegionAvail().x * 0.30f, 600));

		static ImGuiTableFlags europCostFlags = 0;
		europCostFlags |= ImGuiTableFlags_RowBg;
		europCostFlags |= ImGuiTableFlags_Borders;
		europCostFlags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("European Cost", 2, europCostFlags))
		{
			ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Cost", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableHeadersRow();

			DWORD step = 1;

			int i = 0;
			while (Prices::europeanNames[i] != NULL) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(Prices::europeanNames[i]);

				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(i);
				ImGui::InputScalar(Prices::europeanNames[i], ImGuiDataType_U32, &(prices->european->archer) + i, &step, NULL, "%u");
				ImGui::PopID();
				i++;
			}
			ImGui::EndTable();
		}

		static ImGuiTableFlags arabCostFlags = 0;
		arabCostFlags |= ImGuiTableFlags_RowBg;
		arabCostFlags |= ImGuiTableFlags_Borders;
		arabCostFlags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("Arabian Cost", 2, arabCostFlags))
		{
			ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableSetupColumn("Cost", ImGuiTableColumnFlags_WidthFixed, 150.0f);
			ImGui::TableHeadersRow();

			DWORD step = 1;

			int i = 0;
			while (Prices::arabianNames[i] != NULL) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(Prices::arabianNames[i]);

				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(i);
				ImGui::InputScalar(Prices::arabianNames[i], ImGuiDataType_U32, &(prices->arabian->arabianArcher) + i, &step, NULL, "%u");
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
		ImGui::Text(Config::pPricesConfig->mDefaultName.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Selected")) {
			Config::pPricesConfig->Load(Config::pPricesConfig->savedConfigNames[selected]);
			prices->LoadConfig();
		}

		if (ImGui::Button("Save")) {
			prices->PrepareConfig();
			Config::pPricesConfig->Save((std::string)buf);
		}

		ImGui::SameLine();

		if (ImGui::Button("Save as Default")) {
			prices->PrepareConfig();
			Config::pPricesConfig->SaveDefault((std::string)buf);
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Selected")) {
			Config::pPricesConfig->Delete(Config::pPricesConfig->savedConfigNames[selected]);
		}

		ImGui::InputText("Save file name", buf, 64, ImGuiInputTextFlags_CharsNoBlank);

		byte n = 0;
		for (std::basic_string<TCHAR> configFileName : Config::pPricesConfig->savedConfigNames) {
			if (ImGui::Selectable(configFileName.c_str(), selected == n))
				selected = n;
			n++;
		}

		ImGui::EndChild();
	}

	ImGui::SameLine();

	{
		ImGui::BeginChild("Resources Current", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 600));

		static ImGuiTableFlags resourceCostTableFlags = 0;
		resourceCostTableFlags |= ImGuiTableFlags_RowBg;
		resourceCostTableFlags |= ImGuiTableFlags_Borders;
		resourceCostTableFlags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("Resource Cost Current", 3, resourceCostTableFlags))
		{
			ImGui::TableSetupColumn("Resource (Current Game)", ImGuiTableColumnFlags_WidthFixed, 130.0f);
			ImGui::TableSetupColumn("Buy", ImGuiTableColumnFlags_WidthFixed, 130.0f);
			ImGui::TableSetupColumn("Sell", ImGuiTableColumnFlags_WidthFixed, 130.0f);
			ImGui::TableHeadersRow();

			DWORD step = 1;

			for (std::map<std::basic_string<TCHAR>, DWORD>::iterator it = Config::pResourcesConfig->m_ids_map.begin(); it != Config::pResourcesConfig->m_ids_map.end(); it++) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(it->first.c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(Config::pResourcesConfig->m_ids_map[it->first]);
				ImGui::InputScalar("B", ImGuiDataType_U32, &(prices->resource->woodBuy) + (it->second - 2) * 2, &step, NULL, "%u");
				ImGui::TableSetColumnIndex(2);
				ImGui::InputScalar("S", ImGuiDataType_U32, &(prices->resource->woodSell) + (it->second - 2) * 2, &step, NULL, "%u");
				ImGui::PopID();
			}
			ImGui::EndTable();
		}

		ImGui::EndChild();
	}

	ImGui::SameLine();

	{
		ImGui::BeginChild("Resources Global", ImVec2(ImGui::GetContentRegionAvail().x, 600));

		static ImGuiTableFlags resourceCostTableFlags = 0;
		resourceCostTableFlags |= ImGuiTableFlags_RowBg;
		resourceCostTableFlags |= ImGuiTableFlags_Borders;
		resourceCostTableFlags |= ImGuiTableFlags_SizingFixedFit;

		if (ImGui::BeginTable("Resource Cost Global", 3, resourceCostTableFlags))
		{
			ImGui::TableSetupColumn("Resource (Used while starting new game)", ImGuiTableColumnFlags_WidthFixed, 130.0f);
			ImGui::TableSetupColumn("Buy", ImGuiTableColumnFlags_WidthFixed, 130.0f);
			ImGui::TableSetupColumn("Sell", ImGuiTableColumnFlags_WidthFixed, 130.0f);
			ImGui::TableHeadersRow();

			DWORD step = 1;

			for (std::map<std::basic_string<TCHAR>, DWORD>::iterator it = Config::pResourcesConfig->m_ids_map.begin(); it != Config::pResourcesConfig->m_ids_map.end(); it++) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(it->first.c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::PushID(Config::pResourcesConfig->m_ids_map[it->first]);
				ImGui::InputScalar("B", ImGuiDataType_U32, &(prices->globalResource->woodBuy) + (it->second - 2), &step, NULL, "%u");
				ImGui::TableSetColumnIndex(2);
				ImGui::InputScalar("S", ImGuiDataType_U32, &(prices->globalResource->woodSell) + (it->second - 2), &step, NULL, "%u");
				ImGui::PopID();
			}
			ImGui::EndTable();
		}

		ImGui::EndChild();
	}
}