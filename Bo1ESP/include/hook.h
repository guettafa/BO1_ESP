#pragma once

#include "pch.h"

void      PlaceJmp    (char* src, char* dst, size_t size, DWORD* stolenBytes);
uintptr_t Trampoline  (char* src, char* dst, size_t size);

