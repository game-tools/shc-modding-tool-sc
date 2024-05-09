#pragma once

#include <windows.h>
#include <string>

#include "Prices/Base.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

extern DWORD modBase;
extern std::basic_string<TCHAR> dllPathStr;
extern Prices::Base* prices;
extern std::basic_string<TCHAR> characterNames[16];

void setDllPath();
void InitializePrices();
void DeletePrices();