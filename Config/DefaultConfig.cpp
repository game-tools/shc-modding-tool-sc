#include "DefaultConfig.h"

namespace Config {
	Default::Default() {
		Load();
	}

	void Default::Load() {
		std::ifstream f(dllPathStr + "\\defaultConfigs.json");
		mData = json::parse(f);

		f.close();
	}

	void Default::Save() {
		std::ofstream f(dllPathStr + "\\defaultConfigs.json");
		f << mData;
	}
}