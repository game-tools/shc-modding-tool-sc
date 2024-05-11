#include "DefaultInstance.h"

namespace Config {
	Default* pDefaultConfig;

	void InitializeInstanceDefault() {
		pDefaultConfig = new Default();
	}

	void DeleteInstanceDefault() {
		delete pDefaultConfig;
	}
}