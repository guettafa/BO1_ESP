#pragma once

#include "pch.h"
#include <d3d9.h>
#include <dxgi.h>

#define NAKED __declspec(naked)

using Present  = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
using EndScene = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);

namespace Hook
{
	extern std::unordered_map<uintptr_t, bool> entities;

#pragma region Function Ptrs
	extern Present originalPresent;
	extern EndScene originalEndScene;
#pragma endregion

	extern float*							   xPosOfEnt;
	extern uintptr_t						   xPosOfEntAddrs;
	extern uintptr_t						   entityAddrs;
	extern uintptr_t						   codeCaveAddrs;


	HRESULT   __stdcall PresentHook(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
	HRESULT   __stdcall EndSceneHook(IDirect3DDevice9* pDevice);
	void				EntityHook();
	void				PlaceJmp(char* src, char* dst, size_t size, DWORD* stolenBytes);
	uintptr_t			Trampoline(char* src, char* dst, size_t size);
}