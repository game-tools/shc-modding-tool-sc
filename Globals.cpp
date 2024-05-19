#include "Globals.h"

DWORD modBase;
std::basic_string<TCHAR> dllPathStr;
Prices::Base* prices;
std::basic_string<TCHAR> characterNames[16] = { "Rat", "Snake", "Pig", "Wolf", "Saladin", "Caliph", "Sultan", "Richard", "Frederick", "Phillip", "Wazir", "Emir", "Nizar", "Sheriff", "Marshal", "Abbot" };
Market* market;
DWORD* pMaxUnits;
DWORD codeProtect;

std::chrono::steady_clock::time_point start;
std::chrono::steady_clock::time_point stop;
std::chrono::milliseconds duration;

DWORD* pCurrentBottomView;
DWORD* pGamePaused;
DWORD* pGameOptionsActive;
DWORD gameTimeStart;
DWORD gameTimeStop;

void setDllPath()
{
	TCHAR DllPath[MAX_PATH] = { 0 };
	GetModuleFileName((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
	dllPathStr = DllPath;
	dllPathStr.resize(dllPathStr.rfind('\\'));
}

void InitializeGlobals() {
	prices = new Prices::Base();
	market = new Market();
	VirtualProtect((LPVOID)(modBase + 0x59e11), sizeof(0x4), PAGE_EXECUTE_READWRITE, &codeProtect);
	pMaxUnits = (DWORD*)(modBase + 0x59e11);
}

void DeleteGlobals() {
	prices->SetVanillaCode();
	delete prices;
	delete market;
	VirtualProtect((LPVOID)(modBase + 0x59e11), sizeof(0x4), codeProtect, &codeProtect);
}

void ChronoStart() {
	gameTimeStart = *(DWORD*)(modBase + 0xb98adc);
	start = std::chrono::high_resolution_clock::now();
}

void ChronoStop() {
	stop = std::chrono::high_resolution_clock::now();
	gameTimeStop = *(DWORD*)(modBase + 0xb98adc);
}

void ChronoDuration() {
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}

void InitializeInGameVariables() {
	pCurrentBottomView = (DWORD*)(modBase + 0x1bea0f8);
	pGamePaused = (DWORD*)(modBase + 0x9f477c);
	pGameOptionsActive = (DWORD*)(modBase + 0x1f52bc);
}

bool ShouldAddTime() {
	return *pCurrentBottomView > 0 && *pGamePaused == 0 && *pGameOptionsActive == 0 && gameTimeStart != gameTimeStop;
}