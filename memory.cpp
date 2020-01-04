#include "memory.h"
#include <iostream>

void Mem::Patch(BYTE* dist, BYTE* src, unsigned int size) {
	DWORD oldProtect;

	VirtualProtect(dist, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	memcpy(dist, src, size);

	VirtualProtect(dist, size, oldProtect, &oldProtect);
}

void Mem::Nop(BYTE* dist, unsigned int size) {
	DWORD oldProtect;

	VirtualProtect(dist, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	memset(dist, 0x90, size);

	VirtualProtect(dist, size, oldProtect, &oldProtect);
}

uintptr_t Mem::FindAddress(uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t address = ptr;

	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(GetCurrentProcess(), (BYTE*)address, &address, sizeof(address), 0);
		address += offsets[i];
	}
	return address;
}