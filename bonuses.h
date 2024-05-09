#pragma once
#include <functional>
#include <map>
#include <set>

void SetAddresses();
void SetNewTaxes(DWORD modBase);
void GetBonuses();
int GetFoodConsumptionBonus();
int GetFoodTypesBonus();
int GetFearCoeffBonus();
int GetReligionCoeffBonus();
int GetBeerCoeffBonus();
int GetTaxesBonus();
void FindNewTaxesCoeff(int bonusesSum);

DWORD modBaseLocal;
std::map<std::string, int> coeffLocal;

DWORD wholeFoodAddr;
DWORD foodConsumptionRatioAddr;
DWORD foodTypesAddr;
DWORD fearCoeffAddr;
DWORD churchesAmountAddr;
DWORD cathedralAmountAddr;
DWORD religionPercentAddr;
DWORD beerPercentAddr;
DWORD taxesCoeffAddr;

void SetNewTaxes(DWORD modBase) {
	modBaseLocal = modBase;
	SetAddresses();
	GetBonuses();

	int sum = 0;
	for (std::map<std::string, int>::iterator it = coeffLocal.begin(); it != coeffLocal.end(); ++it) {
		sum += it->second;
	}

	FindNewTaxesCoeff(sum);
}

void SetAddresses() {
	wholeFoodAddr = modBaseLocal + 0xd61888;
	foodConsumptionRatioAddr = modBaseLocal + 0xd61978;
	foodTypesAddr = modBaseLocal + 0xd6188c;
	fearCoeffAddr = modBaseLocal + 0xd61920;
	churchesAmountAddr = modBaseLocal + 0xd61a78;
	cathedralAmountAddr = modBaseLocal + 0xd61a7c;
	religionPercentAddr = modBaseLocal + 0xd61a2c;
	beerPercentAddr = modBaseLocal + 0xd61a90;
	taxesCoeffAddr = modBaseLocal + 0xd61974;
}

void GetBonuses() {

	coeffLocal["foodConsumingBonus"] = GetFoodConsumptionBonus();
	coeffLocal["foodTypesBonus"] = GetFoodTypesBonus();
	coeffLocal["fearBonus"] = GetFearCoeffBonus();
	coeffLocal["religionBonus"] = GetReligionCoeffBonus();
	coeffLocal["beerBonus"] = GetBeerCoeffBonus();
	coeffLocal["taxesBonus"] = GetTaxesBonus();
}

int GetFoodConsumptionBonus() {
	std::map<int, int> foodConsumption = { {0, -8}, {1, -4}, {2, 0}, {3, 4}, {4, 8} };

	if (*(int*)wholeFoodAddr <= 0)
		return foodConsumption[0];

	return foodConsumption[*(int*)foodConsumptionRatioAddr];
}

int GetFoodTypesBonus() {
	int foodTypes = *(int*)foodTypesAddr;

	if (foodTypes == 0)
		return 0;

	return foodTypes - 1;
}

int GetFearCoeffBonus() {
	return *(int*)fearCoeffAddr;
}

int GetReligionCoeffBonus() {
	int religionCoeff = 0;
	if (*(int*)churchesAmountAddr > 0)
		religionCoeff += 1;
	if (*(int*)cathedralAmountAddr > 0)
		religionCoeff += 2;

	int religionPercent = *(int*)religionPercentAddr;
	if (religionPercent > 75)
		religionCoeff += 6;
	else if (religionPercent > 50)
		religionCoeff += 4;
	else if (religionPercent > 25)
		religionCoeff += 2;

	return religionCoeff;
}

int GetBeerCoeffBonus() {
	int beerCoeff = 0;
	int beerPercent = *(int*)beerPercentAddr;
	if (beerPercent >= 100)
		beerCoeff += 8;
	else if (beerPercent > 75)
		beerCoeff += 6;
	else if (beerPercent > 50)
		beerCoeff += 4;
	else if (beerPercent > 25)
		beerCoeff += 2;

	return beerCoeff;
}

int GetTaxesBonus() {
	std::map<int, int> taxesBonus = { {0, 7}, {1, 5}, {2, 3}, {3, 1}, {4, -2}, {5, -4}, {6, -6}, {7, -8}, {8, -12}, {9, -16}, {10, -20}, {11, -24} };
	return taxesBonus[*(int*)taxesCoeffAddr];
}

void FindNewTaxesCoeff(int bonusesSum) {
	std::map<int, int> taxesBonus = { {0, 7}, {1, 5}, {2, 3}, {3, 1}, {4, -2}, {5, -4}, {6, -6}, {7, -8}, {8, -12}, {9, -16}, {10, -20}, {11, -24} };

	int bonuses = bonusesSum - coeffLocal["taxesBonus"];

	typedef std::function<bool(std::pair<int, int>, std::pair<int, int>)> Comparator;

	Comparator sortAscending =
		[](std::pair<int, int> tax1, std::pair<int, int> tax2) {
		return tax1.second < tax2.second;
		};

	std::set<std::pair<int, int>, Comparator> setOfTaxes(taxesBonus.begin(), taxesBonus.end(), sortAscending);

	int newTaxesLevel = 3;
	for (std::pair<int, int> element : setOfTaxes) {

		if (bonuses + element.second > 0) {
			newTaxesLevel = element.first;
			if (element.second > 0) {
				newTaxesLevel = 3;
				break;
			}
			break;
		}
	}

	printf("new taxes level: %d\n", newTaxesLevel);
	*(int*)taxesCoeffAddr = newTaxesLevel;
}