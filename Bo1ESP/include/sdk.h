#pragma once

#include <stdint.h>
#include "types.h"
#include <iostream>

namespace SDK
{
	struct clientInfo
	{
		char pad_0000[16];
		int16_t clientNumber; //0x0010
		char pad_0012[2]; 
	}; 

	struct Entity
	{
		char pad_0000[24];
		Vector3 positions;
		char pad_0024[24];
		struct clientInfo* client; //0x003C
		char pad_0040[72]; 
	}; 

	struct Bone 
	{ 
		const char* name; 
		unsigned short id; 
	};

	inline Bone bones[]
	{
		"j_head", 0,
		"j_neck", 0,
		"j_spineupper", 0,
		"j_spinelower", 0,
		"j_elbow_ri", 0,
		"j_elbow_le", 0,
		"j_wrist_ri", 0,
		"j_wrist_le", 0,
		"j_knee_ri", 0,
		"j_knee_le", 0,
		"j_ankle_ri", 0,
		"j_ankle_le", 0
	};

	enum Addresses : uintptr_t
	{
		AGetWorldOriginOfTag	= 0x44A0A0,
		AGetMeshWithClientNum	= 0x501850,
		ARegisterTag			= 0x55ABF0,

		ALocalPlayerEntity		= 0x1a796f8,
		AEntityList				= 0x1A7983C,
		ABoneMatrix				= 0x3AD20AC,
		AEntityHeadPos			= 0x3AD20F8,
		AViewMatrix				= 0x0BA6970,

		// RVA's
		RVAD3d9PresentFunction  = 0x43DE0,
		RVAD3d9EndSceneFunction = 0x66420,
	};

	enum Offsets : uintptr_t
	{
		OffSpaceBetweenEntity = 0x8C,
	};

	extern int	 (__cdecl* GetWorldOriginOfTag ) (Entity* entity, void* mesh, int tagId, Vector3* origin);
	extern int	 (__cdecl* RegisterTag		   ) (const char* tagNameExj_helmet, int typeEntity);
	extern void* (__cdecl* GetMeshWithClientNum) (int clientNum, int zeroVal);

	inline bool GetBoneOrigin(int tagId, Entity* entity, uintptr_t entAddress, Vector3* origin)
	{
		if (entAddress == 0x1a797FC)
			return false;

		void* mesh = GetMeshWithClientNum(entity->client->clientNumber, 0);
		if (mesh == nullptr)
			return false;

		return GetWorldOriginOfTag(entity, mesh, tagId, origin);
	}
}