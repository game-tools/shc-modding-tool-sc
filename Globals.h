#pragma once

#include <windows.h>
#include <string>
#include <chrono>

#include "Prices/Base.h"
#include "Market.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

extern DWORD modBase;
extern std::basic_string<TCHAR> dllPathStr;
extern Prices::Base* prices;
extern std::basic_string<TCHAR> characterNames[16];
extern Market* market;

extern std::chrono::steady_clock::time_point start;
extern std::chrono::steady_clock::time_point stop;
extern std::chrono::milliseconds duration;

extern DWORD* pCurrentBottomView;
extern DWORD* pGamePaused;
extern DWORD* pGameOptionsActive;
extern DWORD gameTimeStart;
extern DWORD gameTimeStop;

void setDllPath();
void InitializeGlobals();
void DeleteGlobals();

void ChronoStart();
void ChronoStop();
void ChronoDuration();

void InitializeInGameVariables();
bool ShouldAddTime();