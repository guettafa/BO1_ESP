#pragma once


namespace Game
{
	struct Vector3 { float x, y, z; };

	class Entity
	{
	public:
		char pad_0000[24];		// 0x0000
		Vector3 xyxPos;			// 0x0018
		char pad_0024[100];		// 0x0024
		int16_t Health;			// 0x0088
		char pad_008A[958];		// 0x008A
	};							// Size: 0x0448
	
	constexpr const uintptr_t localPlayerEntityAddrs = 0x1a796f8;

	namespace RVA
	{
		// From d3d9.dll
		constexpr const uintptr_t d3d9PresentFunction  = 0x43DE0; // RVA Present  Function
		constexpr const uintptr_t d3d9EndSceneFunction = 0x66420; // RVA EndScene Function
	}
}