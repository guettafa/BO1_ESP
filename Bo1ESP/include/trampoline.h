#pragma once

#include <windows.h>
#include <iostream>

#define JMP 0xE9
#define NOP 0x90

void		PlaceJmp(char* src, char* dst, const size_t size, DWORD* stolenBytes)	noexcept;
uintptr_t	Trampoline(char* src, char* dst, const size_t numOfBytes)				noexcept;