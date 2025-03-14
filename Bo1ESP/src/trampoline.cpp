#include "trampoline.h"

void PlaceJmp(char* src, char* dst, size_t size, DWORD* stolenBytes) noexcept
{
	// To restore old state later
	DWORD dwOld;

	// Allow read and writing on the address
	VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &dwOld);

	std::memcpy(stolenBytes, src, size);

	*src = JMP; // Place jmp in the address we want to jump from

	uintptr_t rva = ((uintptr_t)dst - (uintptr_t)src) - 5; // 5 is for the jmp
	*(uintptr_t*)(src + 1) = rva;  // Place rva after the jmp

	if (size - 5 > 0)
		std::memset(src + 5, NOP, size - 5);

	VirtualProtect(src, size, dwOld, &dwOld); // Restore access
}

uintptr_t Trampoline(char* src, char* dst, size_t size) noexcept
{
	BYTE* stolenBytes = new BYTE[size];

	PlaceJmp(src, dst, size, (DWORD*)stolenBytes);

	auto codeCaveAddrs = (char*)VirtualAlloc(nullptr, 100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(codeCaveAddrs, size, stolenBytes, size);

	uintptr_t rvaToGoBack = src - codeCaveAddrs - 5;

	*(uintptr_t*)(codeCaveAddrs + size) = JMP; // place jmp so we can jump back after all stolen bytes
	*(uintptr_t*)(codeCaveAddrs + size + 1) = rvaToGoBack;

	return (uintptr_t)(codeCaveAddrs);
}