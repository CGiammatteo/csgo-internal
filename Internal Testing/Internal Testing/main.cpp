#include <Windows.h>
#include <iostream>
#include <thread>

#include "Offsets.h"
#include "Memory.h"
#include "Entity.h"

#include "Glow.h"
#include "Radar.h"
#include "Chams.h"

DWORD WINAPI main(HMODULE hMod) {
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	std::cout << "Grabbing data..." << std::endl;

	GameGlobals::clientBase = (DWORD)GetModuleHandle(L"client.dll");
	GameGlobals::engineBase = (DWORD)GetModuleHandle(L"engine.dll");

	std::cout << "Client base: " << GameGlobals::clientBase << std::endl;
	std::cout << "Engine base: " << GameGlobals::engineBase << std::endl;
	std::cout << "F1 -> Glow" << std::endl;
	std::cout << "F2 -> Radar" << std::endl;
	std::cout << "F3 -> Chams" << std::endl;
	std::cout << "F4 -> Fov" << std::endl;

	uintptr_t locPlayer = Mem::ReadMemory<uintptr_t>(GameGlobals::clientBase + dwLocalPlayer);

	bool glow = false;
	bool radar = false;
	bool fov = false;
	bool chams = false;

	while (!GetAsyncKeyState(VK_DELETE) & 1) 
	{

		if (GetAsyncKeyState(VK_F1) & 1) {
			glow = !glow;
			std::cout << "Glow: " << glow << std::endl;
		}

		if (GetAsyncKeyState(VK_F2) & 1) {
			radar = !radar;
			std::cout << "Radar: " << radar << std::endl;
		}

		if (GetAsyncKeyState(VK_F3) & 1) {
			chams = !chams;
			std::cout << "Chams: " << chams << std::endl;
		}

		if (GetAsyncKeyState(VK_F4) & 1) {
			fov = !fov;
			if (fov) {
				Mem::WriteMemory<int>(locPlayer + m_iDefaultFOV, 120);
				std::cout << "Fov set to 120"<< std::endl;
			}
			else {
				Mem::WriteMemory<int>(locPlayer + m_iDefaultFOV, 90);
				std::cout << "Fov set to 90" << std::endl;
			}
		}

		if (glow) {
			ToggleGlow();
		}

		if (radar) {
			ToggleRadar();
		}

		if (chams) {
			ToggleChams();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	std::cout << "Closed" << std::endl;
	FreeConsole();
	FreeLibraryAndExitThread(hMod, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hMod, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hMod);
		HANDLE thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hMod, 0, nullptr);
		if (thread)
			CloseHandle(thread);
		break;
	}
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}