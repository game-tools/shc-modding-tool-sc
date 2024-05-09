#include "Definitions.h"

_AddResource AddResource;

_RecruitUnit RecruitUnit;
_SetVariable SetVariable;

void Functions::InitializeDefinitions() {
	AddResource = (_AddResource)(modBase + 0x1c310);

	RecruitUnit = (_RecruitUnit)(modBase + 0x64ef0);
	SetVariable = (_SetVariable)(modBase + 0x805d0);
}