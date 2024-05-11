#pragma once

#include <windows.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../Globals.h"

using json = nlohmann::json;

namespace Config {
	class Default {
	public:
		json mData;
	public:
		Default();
		void Load();
		void Save();
	};
}