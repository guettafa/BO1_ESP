#include "hook.h"


namespace Hook
{
	EndScene originalEndScene = nullptr;

	uintptr_t entityAddrs = 0;
	uintptr_t codeCave    = 0;

	// can be replaced with a Set instead so we dont have to check if already in
	std::unordered_map<uintptr_t, bool> entities{};

	Game::Entity* tempEntity = nullptr;
}

HRESULT __stdcall Hook::EndSceneHook(IDirect3DDevice9* pDevice)
{
	Menu::Init(pDevice);
	Menu::Render();
	
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

	tempEntity = reinterpret_cast<Game::Entity*>(entityAddrs);

	std::printf("size   : %d\n", entities.size());
	std::printf("xpos   : %f\n", tempEntity->xyzPos.x);

	__asm
	{
		jmp[codeCave]
	}
}