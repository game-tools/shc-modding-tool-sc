#pragma once

#include "DefaultConfig.h"

namespace Config {
	extern Default* pDefaultConfig;

	void InitializeInstanceDefault();
	void DeleteInstanceDefault();
}