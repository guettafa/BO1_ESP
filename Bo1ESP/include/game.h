#pragma once

#include "types.h"

namespace SDK
{
	struct Entity
	{
		char pad_0000[24];		//			0x0000
		Vector3 positions;		//			0x0018
		char pad_0024[100];		//			0x0024
		int16_t health;			//			0x0088
		char pad_008A[958];		//			0x008A
	};							// Size	  : 0x0448

	constexpr const uintptr_t ALocalPlayerEntity = 0x1a796f8;
	constexpr const uintptr_t AEntityList		 = 0x1A7983C;
	constexpr const uintptr_t AViewMatrix		 = 0x0BA6970;
	
	namespace Offsets
	{
		constexpr const uintptr_t OffGetTagPos		    = 0x7562C0;
		constexpr const uintptr_t OffSpaceBetweenEntity = 0x8C;
	}
	namespace RVA
	{
		// From d3d9.dll
		constexpr const uintptr_t RVAd3d9PresentFunction  = 0x43DE0; // RVA Present  Function
		constexpr const uintptr_t RVAd3d9EndSceneFunction = 0x66420; // RVA EndScene Function
	}
}