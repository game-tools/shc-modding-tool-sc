#include "Operation.h"

namespace Config {
	Operation::Operation(std::basic_string<TCHAR> configType, bool loadIfNoDefault) {
		mConfigType = configType;
		mDefaultName = "";
		LoadDefault();
		if (loadIfNoDefault && !pDefaultConfig->mData.contains(mConfigType)) {
			Load("vanilla.json");
		}
		GetSavedConfigNames();
	}

	void Operation::Load(std::basic_string<TCHAR> selectedFilename) {
		std::ifstream f(dllPathStr + "\\" + mConfigType + "\\" + selectedFilename);
		mData = json::parse(f);
		f.close();
	}

	void Operation::LoadDefault() {
		if (pDefaultConfig->mData.contains(mConfigType)) {
			mDefaultName = pDefaultConfig->mData[mConfigType];
			std::ifstream f(dllPathStr + "\\" + mConfigType + "\\" + (std::string)pDefaultConfig->mData[mConfigType] + ".json");
			mData = json::parse(f);
			f.close();
		}
	}

	void Operation::Save(std::basic_string<TCHAR> saveFilename) {
		std::ofstream f(dllPathStr + "\\" + mConfigType + "\\" + saveFilename + ".json");
		f << mDataSave;

		GetSavedConfigNames();
	}

	void Operation::SaveDefault(std::basic_string<TCHAR> saveFilename) {
		Save(saveFilename);
		pDefaultConfig->mData[mConfigType] = saveFilename;
		pDefaultConfig->Save();
		mDefaultName = saveFilename;
	}

	void Operation::GetSavedConfigNames() {
		savedConfigNames.clear();
		std::string path = dllPathStr + "\\" + mConfigType;
		for (const auto& entry : fs::directory_iterator(path))
			savedConfigNames.push_back(entry.path().filename().string());
	}

	void Operation::Delete(std::basic_string<TCHAR> selectedFilename) {
		fs::remove(dllPathStr + "\\" + mConfigType + "\\" + selectedFilename);
		if (pDefaultConfig->mData[mConfigType] == selectedFilename.substr(0, selectedFilename.find("."))) {
			pDefaultConfig->mData.erase(mConfigType);
			pDefaultConfig->Save();
			mDefaultName = "";
		}

		GetSavedConfigNames();
	}

	void Operation::RemoveDefault() {
		pDefaultConfig->mData.erase(mConfigType);
		pDefaultConfig->Save();
		mDefaultName = "";
	}
}