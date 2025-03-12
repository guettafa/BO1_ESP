#pragma once

namespace Game
{
	constexpr const uintptr_t localPlayerEntityAddrs = 0x1a796f8;

	/// <summary>
	/// Namespace that contain offsets and Relative Addresses of function in DLL's
	/// </summary>
	namespace Offsets
	{
		constexpr const uintptr_t d3d9PresentFunctionRVA  = 0x43DE0; // RVA Present  Function
		constexpr const uintptr_t d3d9EndSceneFunctionRVA = 0x66420; // RVA EndScene Function
	}
}