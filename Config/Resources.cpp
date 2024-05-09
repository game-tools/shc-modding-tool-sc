#include "Resources.h"

namespace Config {
	Resources::Resources() {
		Load();
		SetToSell();
		SetIds();
	}

	void Resources::Load() {
		std::ifstream f(dllPathStr + "\\trade_config.json");
		m_data = json::parse(f);

		f.close();
	}

	void Resources::SetToSell() {
		for (int resource_id : m_data["resourcesToSell"])
			m_to_sell_map[resource_id] = m_data["sellTo"][std::to_string(resource_id)];
	}

	void Resources::SetIds() {
		for (auto& it : m_data["resources"].items())
			m_ids_map[it.key()] = it.value();
	}
}