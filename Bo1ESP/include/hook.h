#pragma once

#include "pch.h"

extern void      PlaceJmp    (char* src, char* dst, size_t size, DWORD* stolenBytes);
extern uintptr_t Trampoline  (char* src, char* dst, size_t size);

