#include "pch.h"
#include "hook.h"

void PlaceJmp(char* addrsToJumpFrom, char* addrsToJumpTo, size_t numberOfBytes, DWORD* stolenBytes)
{
	// To restore old state we save old state in dwOld
	DWORD dwOld;

	// Allow read and writing on the address
	VirtualProtect(addrsToJumpFrom, numberOfBytes, PAGE_EXECUTE_READWRITE, &dwOld);

	std::memcpy(stolenBytes, addrsToJumpFrom, numberOfBytes); // Save stolen bytes ( to place later in code cave )

	*(uintptr_t*)addrsToJumpFrom = 0xE9; // Place jmp in the address we want to jump from

	// Calculate relative address to know how many we need to jump where we want
	uintptr_t rva = addrsToJumpTo - addrsToJumpFrom - 5; // 5 is for the jmp

	*(addrsToJumpFrom + 1) = rva; // Place rva after the jmp

	if (numberOfBytes - 5 > 5)
		std::memset(addrsToJumpFrom + 5, 0x90, numberOfBytes - 5);

	VirtualProtect(addrsToJumpFrom, numberOfBytes, dwOld, &dwOld); // Restore state
}

uintptr_t Trampoline(char* addrsToJumpFrom, char* addrsToJumpTo, size_t numberOfBytes)
{
	BYTE* stolenBytes = new BYTE[numberOfBytes];

	PlaceJmp(addrsToJumpFrom, addrsToJumpTo, numberOfBytes, reinterpret_cast<DWORD*>(stolenBytes));
	
	// Allocated enough space for our code cave and can read and write on it
	char* codeCaveAddrs = (char*) VirtualAlloc(nullptr, 100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	std::memcpy(codeCaveAddrs, stolenBytes, numberOfBytes); // store stolen bytes

	*(uintptr_t*)(codeCaveAddrs + numberOfBytes) = 0xE9; // place jmp so we can jump back after all stolen bytes

	uintptr_t rvaToGoBack = addrsToJumpFrom - codeCaveAddrs - 5;
	
	*(uintptr_t*)(codeCaveAddrs + numberOfBytes + 1) = rvaToGoBack;

	return (uintptr_t)(codeCaveAddrs);
}

