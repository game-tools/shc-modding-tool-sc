#pragma once

#include "../Player/Player.h"

#include "../imgui/imgui.h"

namespace actionsGui {
	void Render(std::map<DWORD, Player*> playerMap) noexcept;
}