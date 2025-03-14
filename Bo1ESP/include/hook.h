#pragma once

#include <d3d9.h>
#include <unordered_map>

#define NAKED __declspec(naked)

namespace Hook
{
#pragma region Function Ptrs
	using  EndScene = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);
	extern EndScene originalEndScene;
#pragma endregion

	extern std::unordered_map<uintptr_t, bool> entities;

	extern float*							   xPosOfEnt;
	extern uintptr_t						   xPosOfEntAddrs;
	extern uintptr_t						   entityAddrs;
	extern uintptr_t						   codeCave;

	HRESULT   __stdcall EndSceneHook(IDirect3DDevice9* pDevice);										  /// Hooking EndScene d3d9 function to render my own things
	void				EntityHook();																	  /// Retrieve from esi the entity address when function is called and add it to entity vector
}