#pragma once

#include <map>
#include <string>

#include "Arabian.h"
#include "European.h"
#include "ResourcePrices.h"
#include "GlobalResourcePrices.h"

namespace Prices {
	DWORD ArabCost(DWORD unitId);

	class Base {
	public:
		Arabian* arabian;
		European* european;
		Resource* resource;
		GlobalResource* globalResource;
	public:
		Base();
		void InjectArabCost();
		void SetVanillaCode();
		void LoadConfig();
		void PrepareConfig();
	};
}