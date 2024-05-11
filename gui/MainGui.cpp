#include <map>

#include "BotSettingsGui.h"
#include "MainGui.h"
#include "PricesGui.h"
#include "ResourcesGui.h"
#include "UnitsGui.h"
#include "StartGoodsGui.h"
#include "StartTroopsGui.h"
#include "ActionsGui.h"
#include "AutomationsGui.h"
#include "../Player/Player.h"

#include "../imgui/imgui.h"

enum ViewType { ResourcesGui, UnitsGui, BotSettingsGui, PricesGui, StartGoodsGui, StartTroopsGui, ActionsGui, AutomationsGui };
ViewType viewType = ResourcesGui;

std::map<DWORD, Player*> playerMap;
DWORD selectedPlayerNumber = 0;

void MainGui::Render() noexcept {
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::MenuItem("Resources", "Ctrl+R")) { viewType = ResourcesGui; }
		if (ImGui::MenuItem("Units", "Ctrl+U")) { viewType = UnitsGui; }
		if (ImGui::MenuItem("Prices", "Ctrl+P")) { viewType = PricesGui; }
		if (ImGui::MenuItem("Bot Settings", "Ctrl+P")) { viewType = BotSettingsGui; }
		if (ImGui::MenuItem("Starting Goods")) { viewType = StartGoodsGui; }
		if (ImGui::MenuItem("Starting Troops")) { viewType = StartTroopsGui; }
		if (ImGui::MenuItem("Actions")) { viewType = ActionsGui; }
		if (ImGui::MenuItem("Automations")) { viewType = AutomationsGui; }
		ImGui::EndMenuBar();
	}

	if (playerMap.empty()) {
		for (byte i = 0; i < 8; i++) {
			Player* player = new Player(i);
			playerMap[i] = player;
		}
	}
	
	static const char* players_combo_selected_item = playerMap[0]->mPlayerName;

	ImGui::Text("Player: %d", selectedPlayerNumber);

	ImGui::SameLine();
	static ImGuiComboFlags players_combo_flags = 0;
	players_combo_flags |= ImGuiComboFlags_WidthFitPreview;

	if (ImGui::BeginCombo("PlayersCombo", players_combo_selected_item, players_combo_flags))
	{
		for (std::map<DWORD, Player*>::iterator it = playerMap.begin(); it != playerMap.end(); it++) {
			bool is_selected = (players_combo_selected_item == it->second->mPlayerName);
			if (ImGui::Selectable(it->second->mPlayerName, is_selected)) {
				players_combo_selected_item = it->second->mPlayerName;
				selectedPlayerNumber = it->first;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::SameLine();

	if (ImGui::Button("Reload Players")) {
		for (std::map<DWORD, Player*>::iterator it = playerMap.begin(); it != playerMap.end(); it++) {
			delete it->second;
		}
		playerMap.clear();

		for (byte i = 0; i < 8; i++) {
			Player* player = new Player(i);
			playerMap[i] = player;
		}
	}

	ImGui::Separator();

	switch (viewType)
	{
	case ResourcesGui: {
		resourcesGui::Render(playerMap, selectedPlayerNumber);
		break;
	}
	case UnitsGui: {
		unitsGui::Render(playerMap, selectedPlayerNumber);
		break;
	}
	case BotSettingsGui: {
		botSettingsGui::Render();
		break;
	}
	case PricesGui: {
		pricesGui::Render();
		break;
	}
	case StartGoodsGui: {
		startGoodsGui::Render();
		break;
	}
	case StartTroopsGui: {
		startTroopsGui::Render();
		break;
	}
	case ActionsGui: {
		actionsGui::Render(playerMap);
		break;
	}
	case AutomationsGui: {
		automationsGui::Render();
		break;
	}
	}

	for (byte i = 0; i < 8; i++) {
		if (playerMap[i]->mInstantRecruits)
			*(DWORD*)(0x115f858 + 0x39f4 * i) = 4000;
	}
}