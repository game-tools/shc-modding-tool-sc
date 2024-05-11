#include "Globals.h"

DWORD modBase;
std::basic_string<TCHAR> dllPathStr;
Prices::Base* prices;
std::basic_string<TCHAR> characterNames[16] = { "Rat", "Snake", "Pig", "Wolf", "Saladin", "Caliph", "Sultan", "Richard", "Frederick", "Phillip", "Wazir", "Emir", "Nizar", "Sheriff", "Marshal", "Abbot" };

void setDllPath()
{
	TCHAR DllPath[MAX_PATH] = { 0 };
	GetModuleFileName((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
	dllPathStr = DllPath;
	dllPathStr.resize(dllPathStr.rfind('\\'));
}

void InitializePrices() {
	prices = new Prices::Base();
}

void DeletePrices() {
	prices->SetVanillaCode();
	delete prices;
}