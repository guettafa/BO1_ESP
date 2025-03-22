#pragma once

#include <d3d9.h>
#include <unordered_map>
#include <iostream>

#include "game.h"
#include "menu.h"

#define NAKED __declspec(naked)

namespace Hook
{
#pragma region Game Function Ptrs
	using  EndScene = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);
	extern EndScene OEndScene;

	using  GetTagPos = HRESULT(__cdecl*)(SDK::Entity* entity, void* mesh, short boneTag, Vector3 origin);
	extern GetTagPos OGetTagPos;
#pragma endregion

	extern uintptr_t							AEntity;
	extern uintptr_t							ACodeCave;
	extern std::unordered_map<uintptr_t, bool>	entities;
	extern SDK::Entity*							tempEntity;

#pragma region Hooks
	HRESULT   __stdcall EndSceneHook(IDirect3DDevice9* pDevice); // Hooking EndScene d3d9 function to render my own things
	void				EntityHook();							 // Retrieve from esi the entity address when function is called and add it to entity vector
#pragma endregion
}