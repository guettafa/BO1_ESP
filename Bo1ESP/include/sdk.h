#pragma once

#include <stdint.h>
#include "types.h"

namespace SDK
{
	struct Entity
	{
		char pad_0000[24];		
		Vector3 positions;		
		char pad_0024[100];		
		int16_t health;			
		char pad_008A[958];		
	};						

	enum Addresses : uintptr_t
	{
		AGetTagPos				= 0x757C80,
		AFindBoneIdWithName		= 0x687530,
		ALocalPlayerEntity		= 0x1a796f8,
		AEntityList				= 0x1A7983C,
		AViewMatrix				= 0x0BA6970,

		// RVA's
		RVAD3d9PresentFunction  = 0x43DE0,
		RVAD3d9EndSceneFunction = 0x66420,
	};

	enum Offsets : uintptr_t
	{
		OffSpaceBetweenEntity = 0x8C,
	};

	extern int	 (__cdecl* FindBoneWithId) (char* boneName, int a2);
	extern char* (*		   GetTagPos)	   (float* origin, Entity* entity, char* boneTag);
}