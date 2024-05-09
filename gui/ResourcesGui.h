#pragma once

#include <map>

#include "../Player/Player.h"
#include "../Globals.h"

namespace resourcesGui
{
	void Render(std::map<DWORD, Player*> playerMap, DWORD selectedPlayerNumber) noexcept;
}