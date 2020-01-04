#include <windows.h>
#include <TlHelp32.h>
#include <vector>

namespace Mem {
	void Patch(BYTE* dist, BYTE* src, unsigned int size);
	void Nop(BYTE* dist, unsigned int size);
	uintptr_t FindAddress(uintptr_t ptr, std::vector<unsigned int> offsets);
	
}