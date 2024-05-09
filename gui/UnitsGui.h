#pragma once

#include <map>

#include "../Player/Player.h"

namespace unitsGui
{
	void Render(std::map<DWORD, Player*> playerMap, DWORD selectedPlayerNumber) noexcept;
}
