#pragma once

#include <windows.h>

namespace Prices {
	extern const char* europeanNames[];

	class European {
	public:
		DWORD archer;
		DWORD crossbowman;
		DWORD spearman;
		DWORD pikeman;
		DWORD maceman;
		DWORD swordsman;
		DWORD knight;
	};
}