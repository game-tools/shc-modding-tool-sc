#include "Resources.h"

namespace Config {
	Resources::Resources() {
		Load();
		SetIds();
	}

	void Resources::Load() {
		std::ifstream f(dllPathStr + "\\trade_config.json");
		m_data = json::parse(f);

		f.close();
	}

	void Resources::SetIds() {
		for (auto& it : m_data["resources"].items())
			m_ids_map[it.key()] = it.value();
	}
}