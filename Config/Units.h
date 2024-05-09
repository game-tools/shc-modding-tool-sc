#pragma once

#include <windows.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../Globals.h"

using json = nlohmann::json;

namespace Config {
	class Units {
	public:
		json mData;
	public:
		Units();
		void Load();
	};
}