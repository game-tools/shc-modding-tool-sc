#include <windows.h>

#include "ActionsBase.h"
#include "ActionsTents.h"
#include "../Globals.h"

namespace Actions {
	ActionsTents* pActionsTents;
	ActionsGates* pActionsGates;
	ActionsGameSpeed* pActionsGameSpeed;

	void InitializeInstances() {
		pActionsTents = new ActionsTents();
		pActionsGates = new ActionsGates();
		pActionsGameSpeed = new ActionsGameSpeed();
	}

	void DeleteInstances() {
		delete pActionsTents;
		delete pActionsGates;
		delete pActionsGameSpeed;
	}
}