#include "pch.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <tlhelp32.h>

#include "Globals.h"
#include "bonuses.h"
#include "gui/gui.h"
#include "Unit.h"
#include "Config/DefaultInstance.h"
#include "Config/Instances.h"
#include "Automations/AutomationsInstances.h"
#include "Bot/BotInstances.h"
#include "Functions/Definitions.h"
#include "Start/StartInstances.h"

BOOLEAN autoTaxes = false;
BOOLEAN visible = true;

void PrintMenu()
{
	for (int n = 0; n < 5; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");
	printf("----- Created by FunDemandingProgramming -----\n");
	printf("Stronghold Crusader simple bot\n");
	printf("1. Sell Resources\n");
	printf("4. Set Tax level\n");
	printf("6. Auto selling");
	printf("7. Auto taxes");
}

DWORD WINAPI MainThread(LPVOID param) {
	modBase = (DWORD)GetModuleHandle(NULL);
	setDllPath();
	InitializeInGameVariables();

	Config::InitializeInstanceDefault();
	Config::InitializeInstances();
	Automations::InitializeInstances();
	Bot::InitializeInstances();
	Functions::InitializeDefinitions();
	InitializeGlobals();
	Start::InitializeInstances();
	

	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();

	Unit unit;
	
	while (gui::exit) {
		if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		{
			visible = !visible;

			if (visible)
				gui::ShowWindow();
			else
				gui::HideWindow();
		}

		if (visible)
		{
			gui::BeginRender();
			gui::Render();
			gui::EndRender();
		}

		ChronoStart();

		if ((GetAsyncKeyState(VK_NUMPAD1) & 1) || (market->mCurrentResourcesTimer > *market->mSellResourcesInterval && market->mAutoSelling)) {
			market->Sell();

			if (market->mCurrentResourcesTimer > *market->mSellResourcesInterval)
				market->mCurrentResourcesTimer = 0;
		}

		if ((GetAsyncKeyState(VK_NUMPAD4) & 1) || (unit.mCurrentTaxesTimer > unit.mAutoTaxesInterval && autoTaxes)) {
			SetNewTaxes(modBase);

			if (unit.mCurrentTaxesTimer > unit.mAutoTaxesInterval)
				unit.mCurrentTaxesTimer = 0;
		}

		if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
			market->mAutoSelling = !market->mAutoSelling;
			market->mCurrentResourcesTimer = 0;
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
			autoTaxes = !autoTaxes;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(25));
		ChronoStop();
		ChronoDuration();

		if (ShouldAddTime()) {
			market->mCurrentResourcesTimer += duration.count();
			unit.mCurrentTaxesTimer += duration.count();
		}
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	Automations::DeleteInstances();
	Config::DeleteInstances();
	Config::DeleteInstanceDefault();
	DeleteGlobals();

	FreeLibraryAndExitThread((HINSTANCE)param, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
