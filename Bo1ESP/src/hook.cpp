#include "hook.h"


namespace Hook
{
	EndScene originalEndScene = nullptr;

	std::unordered_map<uintptr_t, bool> entities{};
	uintptr_t entityAddrs			 = 0;
	uintptr_t xPosOfEntAddrs		 = 0;
	uintptr_t codeCave			     = 0;

	Game::Entity* entity = nullptr;
	//float* xPosOfEnt = nullptr;
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

	entity = reinterpret_cast<Game::Entity*>(entityAddrs);

	std::printf("size   : %d\n", entities.size());
	std::printf("xpos   : %f\n", entity->xyxPos.x);

	__asm
	{
		jmp[codeCave]
	}
}