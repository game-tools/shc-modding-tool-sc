#include "Instances.h"

namespace Config {
	Resources* pResourcesConfig;
	Units* pUnitsConfig;

	void InitializeInstances() {
		pResourcesConfig = new Resources();
		pUnitsConfig = new Units();
	}

	void DeleteInstances() {
		delete pResourcesConfig;
		delete pUnitsConfig;
	}
}