//my first version of this cheat

#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "memory.h"

DWORD WINAPI SummerThread(HMODULE hModule)
{
	AllocConsole();

	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	HANDLE handle = GetModuleHandle("game.exe");

	bool flyHack = false;

	uintptr_t moduleBase = (uintptr_t)handle;

	while (true)
	{
		uintptr_t y_address = Mem::FindAddress(moduleBase + 0x00504AA0, { 0x14 });
		float* y = (float*)y_address;
		ReadProcessMemory(handle, (BYTE*)y_address, &y, sizeof(y), nullptr);

		std::cout << "y address = " << "0x" << std::hex << y_address << std::endl;
		std::cout << "flyHack = " << flyHack << std::endl;

		if (GetAsyncKeyState(VK_SHIFT)) {
			*y += 6;
			WriteProcessMemory(handle, (BYTE*)y_address, &y, sizeof(y), nullptr);
		}
		if (GetAsyncKeyState(VK_CONTROL)) {
			*y -= 6;
			WriteProcessMemory(handle, (BYTE*)y_address, &y, sizeof(y), nullptr);
		}
		if (GetAsyncKeyState(VK_BACK)) {
			break;
		}

		if (GetAsyncKeyState(VK_F1)) {
			flyHack = !flyHack; 

			if (flyHack) {
				Mem::Nop((BYTE*)(moduleBase + 0x4D6D1), 3);
			}
			else
			{
				Mem::Patch((BYTE*)(moduleBase + 0x4D6D1), (BYTE*)"\x89\x51\x04", 3);
			}

		}
		
		system("cls");
	}


	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
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
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)SummerThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}