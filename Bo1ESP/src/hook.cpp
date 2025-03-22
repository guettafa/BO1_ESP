#include "hook.h"
#include "drawer.h"

namespace Hook
{						   
	EndScene       OEndScene	   = nullptr;

	uintptr_t AEntity	= 0;
	uintptr_t ACodeCave	= 0;

	std::unordered_map<uintptr_t, bool> entities{};
}

HRESULT __stdcall Hook::EndSceneHook(IDirect3DDevice9* pDevice)
{
	Menu::Init(pDevice);
	Menu::Render();
	
	return OEndScene(pDevice);
}

NAKED void Hook::EntityHook()
{
	__asm
	{
		mov[AEntity], esi
	}

	if (!entities[AEntity] && AEntity != SDK::ALocalPlayerEntity)
		entities[AEntity] += 1;

	__asm
	{
		jmp[ACodeCave]
	}
}