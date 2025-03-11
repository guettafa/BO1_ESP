#include "pch.h"
#include "hook.h"
#include "game.h"
#include <iostream>

namespace Hook
{
	// Function Pointers for Hooks
	Present  originalPresent  = nullptr;
	EndScene originalEndScene = nullptr;

	std::unordered_map<uintptr_t, bool> entities{};
	uintptr_t entityAddrs			 = 0;
	uintptr_t xPosOfEntAddrs		 = 0;
	uintptr_t codeCaveAddrs			 = 0;

	float* xPosOfEnt = nullptr;
}

HRESULT __stdcall Hook::PresentHook(IDirect3DDevice9* pDevice, const RECT* pSrcRect, const RECT* pDestRect, HWND hWindow, const RGNDATA* pRegion)
{
	// Own Rendering

	std::cout << "Hooked d3d9 PRESENT !" << std::endl;

	return originalPresent(pDevice, pSrcRect, pDestRect, hWindow, pRegion);
}

HRESULT __stdcall Hook::EndSceneHook(IDirect3DDevice9* pDevice)
{
	// Own Rendering
	if (pDevice != nullptr)
	{
		std::cout << "Hooked d3d9 EndScene !" << std::endl;
	}

	return originalEndScene(pDevice);
}

NAKED void Hook::EntityHook()
{
	__asm
	{
		mov[entityAddrs], esi
	}

	if (!entities[entityAddrs] && entityAddrs != Game::localPlayerEntityAddrs)
		entities[entityAddrs] += 1;

	xPosOfEnt = reinterpret_cast<float*>(entityAddrs + 0x18);

	std::printf("size   : %d\n", entities.size());
	std::printf("xpos   : %f\n", *xPosOfEnt);

	__asm
	{
		jmp[codeCaveAddrs]
	}
}

void Hook::PlaceJmp(char* src, char* dst, size_t size, DWORD* stolenBytes)
{
	// To restore old state later
	DWORD dwOld;

	// Allow read and writing on the address
	VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &dwOld);

	std::memcpy(stolenBytes, src, size);

	*src = 0xE9; // Place jmp in the address we want to jump from

	uintptr_t rva = ((uintptr_t)dst - (uintptr_t)src) - 5; // 5 is for the jmp
	*(uintptr_t*)(src + 1) = rva;  // Place rva after the jmp

	if (size - 5 > 0)
		std::memset(src + 5, 0x90, size - 5);

	VirtualProtect(src, size, dwOld, &dwOld); // Restore access
}

uintptr_t Hook::Trampoline(char* src, char* dst, size_t size)
{
	BYTE* stolenBytes = new BYTE[size];

	PlaceJmp(src, dst, size,(DWORD*)stolenBytes);
	
	char* codeCaveAddrs = (char*) VirtualAlloc(nullptr, 100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(codeCaveAddrs, size, stolenBytes, size);

	uintptr_t rvaToGoBack = src - codeCaveAddrs - 5;
	
	*(uintptr_t*)(codeCaveAddrs + size)     = 0xE9; // place jmp so we can jump back after all stolen bytes
	*(uintptr_t*)(codeCaveAddrs + size + 1) = rvaToGoBack;

	return (uintptr_t)(codeCaveAddrs);
}

