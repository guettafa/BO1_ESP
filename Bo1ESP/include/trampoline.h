#pragma once

#include <windows.h>
#include <iostream>
#include "opcode.h"

void		PlaceJmp(char* src, char* dst, size_t size, DWORD* stolenBytes) noexcept;
uintptr_t	Trampoline(char* src, char* dst, size_t size) noexcept;