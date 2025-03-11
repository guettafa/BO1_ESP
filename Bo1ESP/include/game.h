#pragma once

#include "pch.h"

namespace Game
{
	constexpr const uintptr_t localPlayerEntityAddrs = 0x1a796f8;

	namespace Offsets
	{
		constexpr const uintptr_t d3d9PresentFunctionOffsets  = 0x43DE0;
		constexpr const uintptr_t d3d9EndSceneFunctionOffsets = 0x66420;
	}
}