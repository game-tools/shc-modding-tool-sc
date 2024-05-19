#pragma once

#include <windows.h>

namespace Units {
	const char* damageLabels[];
	const char* nameLabels[];

	class UnitsBase {
	public:
		DWORD u1;
		DWORD u2[0x4];
		DWORD tunneler;
		DWORD u3[0x10];
		DWORD archer;
		DWORD crossbowman;
		DWORD spearman;
		DWORD pikeman;
		DWORD maceman;
		DWORD swordsman;
		DWORD knight;
		DWORD ladderman;
		DWORD engineer;
		DWORD u4[0x6];
		DWORD monk;
		DWORD u5;
		DWORD catapult;
		DWORD trebuchet;
		DWORD mangonnel;
		DWORD u6[0xd];
		DWORD lord;
		DWORD u7[0x2];
		DWORD siegeTower;
		DWORD batteringRam;
		DWORD shield;
		DWORD ballista;
		DWORD u8[0x8];
		DWORD arabianArcher;
		DWORD slave;
		DWORD slinger;
		DWORD assassin;
		DWORD horseArcher;
		DWORD arabianSwordsman;
		DWORD fireThrower;
		DWORD fireBallista;
	};
}