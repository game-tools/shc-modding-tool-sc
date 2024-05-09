#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <iostream>

#include "PlayerResources.h"
#include "PlayerUnits.h"
#include "../Globals.h"

class Player
{
public:
	DWORD mPlayerNumber;
	DWORD* mPlayerTeam;
	BYTE mInstantRecruits;
	PlayerResources mPlayerResources;
	PlayerUnits mPlayerUnits;
	char* mPlayerName;
public:
	Player(DWORD playerNumber);
};

#endif
