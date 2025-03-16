#include "hook.h"
#include "drawer.h"

namespace Hook
{
	EndScene  AOriginalEndScene = nullptr;
	uintptr_t AEntity			= 0;
	uintptr_t ACodeCave			= 0;

	ImVec2 xyPos = ImVec2(0, 0);

	// can be replaced with a Set instead so we dont have to check if already in
	std::unordered_map<uintptr_t, bool> entities{};

	Game::Entity* tempEntity   = nullptr;
}

HRESULT __stdcall Hook::EndSceneHook(IDirect3DDevice9* pDevice)
{
	Menu::Init(pDevice);
	Menu::Render();
	
	return AOriginalEndScene(pDevice);
}

NAKED void Hook::EntityHook()
{
	__asm
	{
		mov[AEntity], esi
	}

	if (!entities[AEntity] && AEntity != Game::AlocalPlayerEntity)
		entities[AEntity] += 1;

	__asm
	{
		jmp[ACodeCave]
	}
}