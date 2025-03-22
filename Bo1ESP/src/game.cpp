#include "game.h"

namespace SDK
{
	int		(__cdecl* FindBoneWithId) (char* boneName, int a2)						 = (int   (__cdecl*)(char*, int))			 (Addresses::AFindBoneIdWithName);
	char*	(*GetTagPos)			  (float* origin, Entity* entity, char* boneTag) = (char* (		  *)(float*, Entity*, char*))(Addresses::AGetTagPos);
};