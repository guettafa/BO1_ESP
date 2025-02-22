#pragma once

#include "pch.h"

#define NAKED __declspec(naked)

//0x1a796f8

namespace Hook
{
	extern std::unordered_map<uintptr_t, bool> entities;

	extern uintptr_t						   entityAddrs;
	extern uintptr_t						   localPlayerEntityAddrs;
	extern uintptr_t						   xPosOfEntAddrs;
	extern uintptr_t						   codeCaveAddrs;

	extern float*							   xPosOfEnt;

	void      EntityHook();

	void      PlaceJmp(char* src, char* dst, size_t size, DWORD* stolenBytes);
	uintptr_t Trampoline(char* src, char* dst, size_t size);
}