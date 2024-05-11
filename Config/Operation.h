#pragma once

#include <windows.h>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

#include "../Globals.h"
#include "DefaultInstance.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace Config {
	class Operation {
	public:
		json mData;
		json mDataSave;
		std::basic_string<TCHAR> mConfigType;
		std::basic_string<TCHAR> mDefaultName;
		std::vector<std::basic_string<TCHAR>> savedConfigNames;
	public:
		Operation(std::basic_string<TCHAR> configType, bool loadIfNoDefault);
		void Load(std::basic_string<TCHAR> selectedFilename);
		void LoadDefault();
		void Save(std::basic_string<TCHAR> saveFilename);
		void SaveDefault(std::basic_string<TCHAR> saveFilename);
		void GetSavedConfigNames();
		void Delete(std::basic_string<TCHAR> selectedFilename);
		void RemoveDefault();
	};
}
