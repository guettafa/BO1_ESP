#pragma once

#include "pch.h"

void      PlaceJmp   (char* addrsToJumpFrom, char* addrsToJumpTo, size_t numberOfBytes, DWORD* stolenBytes);
uintptr_t Trampoline (char* addrsToJumpFrom, char* addrsToJumpTo, size_t numberOfBytes);