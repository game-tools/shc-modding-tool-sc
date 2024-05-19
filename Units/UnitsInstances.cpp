#include "UnitsInstances.h"
#include "../Config/Instances.h"
#include "../Globals.h"

// unit size 0x490
// damage arr size 0x140

namespace Units {
	UnitsBase* pUnitHps;
	std::vector<UnitsBase*> pUnitDamage;

	void InitializeInstances() {
		pUnitHps = (UnitsBase*)(modBase + 0x74e960);
		
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x753320));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x74eaa0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x7509e0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x7545e0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x754ae0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x74ebe0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x754860));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x74ed20));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x750b20));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x74f4a0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x750c60));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x750da0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x750ee0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x751020));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x751160));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x754720));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x7549a0));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x754c20));
		pUnitDamage.push_back((UnitsBase*)(modBase + 0x754d60));
	}

	void LoadConfig() {
		if (Config::pUnitPropertiesConfig->mData.contains("unitHps")) {
			byte index = 0;
			for (DWORD value : Config::pUnitPropertiesConfig->mData["unitHps"]) {
				*(DWORD*)(&pUnitHps->u1 + index) = value;
				index++;
			}
		}

		byte index = 0;
		while (Units::damageLabels[index] != NULL) {
			if (Config::pUnitPropertiesConfig->mData.contains(Units::damageLabels[index])) {
				byte propertyIndex = 0;
				for (DWORD value : Config::pUnitPropertiesConfig->mData[Units::damageLabels[index]]) {
					*(DWORD*)(&pUnitDamage[index]->u1 + propertyIndex) = value;
					propertyIndex++;
				}
			}
			index++;
		}
	}

	void PrepareConfig() {
		Config::pUnitPropertiesConfig->mDataSave = {};

		DWORD hpValues[78];
		for (int i = 0; i < 78; i++) {
			hpValues[i] = *(DWORD*)(&pUnitHps->u1 + i);
		}
		Config::pUnitPropertiesConfig->mDataSave["unitHps"] = hpValues;

		byte index = 0;
		while (Units::damageLabels[index] != NULL) {
			DWORD values[78];
			for (int i = 0; i < 78; i++) {
				values[i] = *(DWORD*)(&pUnitDamage[index]->u1 + i);
			}
			Config::pUnitPropertiesConfig->mDataSave[Units::damageLabels[index]] = values;
			index++;
		}
	}
}