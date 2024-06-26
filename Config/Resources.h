#pragma once

#include <windows.h>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../Globals.h"

using json = nlohmann::json;

namespace Config {
	class Resources {
	public:
		json m_data;
		// <resourceName, resourceId>
		std::map<std::basic_string<TCHAR>, DWORD> m_ids_map;
	public:
		Resources();
		void Load();
		void SetIds();
	};
}
