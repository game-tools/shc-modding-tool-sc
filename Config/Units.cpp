#include "Units.h"

namespace Config {
	Units::Units() {
		Load();
	}

	void Units::Load() {
		std::ifstream f(dllPathStr + "\\unit_config.json");
		mData = json::parse(f);

		f.close();
	}
}