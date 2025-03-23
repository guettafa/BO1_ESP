#pragma once

#include <stdint.h>
#include "types.h"
#include <iostream>

namespace SDK
{
	//struct Entity
	//{
	//	char pad_0000[24];
	//	Vector3 positions;
	//	char pad_0024[100];
	//	int16_t health;
	//	char pad_008A[958];
	//};

	struct clientInfo
	{
		char pad_0000[16]; //0x0000
		int16_t clientNumber; //0x0010
		char pad_0012[2]; //0x0012
	}; //Size: 0x0014

	struct Entity
	{
		char pad_0000[24]; //0x0000
		Vector3 positions; //0x0018
		char pad_0024[24]; //0x0024
		struct clientInfo* client; //0x003C
		char pad_0040[72]; //0x0040
	}; //Size: 0x0088

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

	extern int	 (__cdecl* GetWorldOriginOfTag ) (Entity* entity, void* mesh, int tagId, float* origin);
	extern int	 (__cdecl* RegisterTag		   ) (const char* tagNameExj_helmet, int typeEntity);
	extern void* (__cdecl* GetMeshWithClientNum) (int clientNum, int zeroVal);

	inline bool GetBoneOrigin(int tagId, Entity* entity, uintptr_t entAddress, float* origin)
	{
		if (entAddress == 0x1a797FC)
			return false;

		void* mesh = GetMeshWithClientNum(entity->client->clientNumber, 0);
		if (mesh == nullptr)
			return false;

		return GetWorldOriginOfTag(entity, mesh, tagId, origin);
	}
}