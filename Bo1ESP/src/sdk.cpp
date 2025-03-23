#include "sdk.h"

namespace SDK
{
	int		(__cdecl* GetWorldOriginOfTag)	(Entity* entity, void* mesh, int tagId, Vector3* origin) = (int	  (__cdecl*)(Entity*, void*, int, Vector3*) )(Addresses::AGetWorldOriginOfTag);
	int		(__cdecl* RegisterTag)			(const char* tagNameExj_helmet, int typeEntity)		   = (int	  (__cdecl*)(const char*, int))(Addresses::ARegisterTag);
	void*	(__cdecl* GetMeshWithClientNum) (int clientNum, int zeroVal)						   = (void*	  (__cdecl*)(int, int))(Addresses::AGetMeshWithClientNum);
};