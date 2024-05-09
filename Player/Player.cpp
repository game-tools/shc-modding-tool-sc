#include "Player.h"

DWORD playerNamesBaseOffset = 0x162347e;
DWORD playerNameBufferSize = 0xfa;
DWORD playerTeamIdBaseOffset = 0xd7d54c;

Player::Player(DWORD playerNumber) {
	mPlayerResources = PlayerResources(playerNumber);
	mPlayerUnits = PlayerUnits(playerNumber);
	mPlayerNumber = playerNumber;
	mInstantRecruits = 0;
	mPlayerTeam = (DWORD*)(modBase + playerTeamIdBaseOffset + 0x4 * mPlayerNumber);
	mPlayerName = (char*)(modBase + playerNamesBaseOffset + playerNameBufferSize * mPlayerNumber);
}