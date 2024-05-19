#pragma once

#include "ActionsTents.h"
#include "ActionsGates.h"
#include "ActionsGameSpeed.h"

namespace Actions {
	extern ActionsTents* pActionsTents;
	extern ActionsGates* pActionsGates;
	extern ActionsGameSpeed* pActionsGameSpeed;

	void InitializeInstances();
	void DeleteInstances();
}