#pragma once

#include "pch.h"
#include <d3d9.h>
#include <dxgi.h>

#define NAKED __declspec(naked)

//0x1a796f8


namespace Hook
{
	// Function Ptr for IDXGISwapChain::Present function

	extern std::unordered_map<uintptr_t, bool> entities;

	// For testing
	extern float*							   xPosOfEnt;
	extern uintptr_t						   xPosOfEntAddrs;
	extern uintptr_t						   entityAddrs;
	extern uintptr_t						   codeCaveAddrs;

	void      EntityHook();
	void      PlaceJmp(char* src, char* dst, size_t size, DWORD* stolenBytes);
	uintptr_t Trampoline(char* src, char* dst, size_t size);
}