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
#include "Market.h"
#include "Unit.h"
#include "Config/Instances.h"
#include "Bot/BotInstances.h"
#include "Functions/Definitions.h"
#include "Start/StartInstances.h"

BOOLEAN autoSelling = false;
BOOLEAN autoTaxes = false;
BOOLEAN visible = true;

void PrintMenu()
{
	for (int n = 0; n < 5; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");
	printf("----- Created by FunDemandingProgramming -----\n");
	printf("Stronghold Crusader simple bot\n");
	printf("1. Sell Resources\n");
	printf("2. Recruit Unit assigned to Numpad 2\n");
	printf("3. Recruit Unit assigned to Numpad 3\n");
	printf("4. Set Tax level\n");
	printf("6. Auto selling: % s\n", autoSelling ? "on" : "off");
	printf("7. Auto taxes: % s\n", autoTaxes ? "on" : "off");
	printf("9. Unload DLL\n");
}

DWORD WINAPI MainThread(LPVOID param) {
	modBase = (DWORD)GetModuleHandle(NULL);
	setDllPath();

	Config::InitializeInstances();
	Bot::InitializeInstances();
	Functions::InitializeDefinitions();
	InitializePrices();
	Start::InitializeInstances();
	

	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();

	Market market;
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

		auto start = std::chrono::high_resolution_clock::now();

		if ((GetAsyncKeyState(VK_NUMPAD1) & 1) || (market.getMCurrentResourcesTimer() > market.getMSellResourcesInterval() && autoSelling)) {
			market.sell();

			if (market.getMCurrentResourcesTimer() > market.getMSellResourcesInterval())
				market.setMCurrentResourcesTimer(0);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
			unit.recruit("2");

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
			unit.recruit("3");

		if ((GetAsyncKeyState(VK_NUMPAD4) & 1) || (unit.getMCurrentTaxesTimer() > unit.getMAutoTaxesInterval() && autoTaxes)) {
			SetNewTaxes(modBase);

			if (unit.getMCurrentTaxesTimer() > unit.getMAutoTaxesInterval())
				unit.setMCurrentTaxesTimer(0);
		}

		if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
			autoSelling = !autoSelling;
			PrintMenu();
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
			autoTaxes = !autoTaxes;
			PrintMenu();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		market.setMCurrentResourcesTimer(market.getMCurrentResourcesTimer() + duration.count());
		unit.setMCurrentTaxesTimer(unit.getMCurrentTaxesTimer() + duration.count());
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	Config::DeleteInstances();
	DeletePrices();

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
