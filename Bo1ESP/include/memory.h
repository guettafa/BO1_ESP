#pragma once

#include <windows.h>
#include <psapi.h>
#include <string>
#include <iostream>

#define JMP 0xE9
#define NOP 0x90

constexpr const char* PEntityInstruction = "\xF3\x0F\x11\x86\x04\x01\x00\x00\xF3\x0F\x10\x86\xEC\x00\x00\x00\xF3\x0F\x58\x86\x20\x01\x00\x00\xF3\x0F\x11\x86\x08\x01\x00\x00\xF3\x0F\x10\x86\xF0\x00\x00\x00\xF3\x0F\x58\x86\x24\x01\x00\x00\x8D\xBE\x04\x01\x00\x00";
constexpr const char* PGetTagPosition	 = "\x0F\xB6\x46\x00\x00\x00\x8B\x8E\x00\x00\x00\x00\x00\x00\x00\x00\x00\x53\x8B\x5C\x24\x08\x50\x51";

MODULEINFO  GetModuleInfo	(const wchar_t* moduleName)											noexcept;
uintptr_t   FindPattern		(const wchar_t* moduleName, const char* pattern, int patternLength) noexcept;
void		PlaceJmp		(char* src, char* dst, const size_t size, DWORD* stolenBytes)		noexcept;
uintptr_t	Trampoline		(char* src, char* dst, const size_t numOfBytes)						noexcept;