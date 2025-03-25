#include "drawer.h"

typedef int(__cdecl* GScr_AllocString_t)(const char* s); 
static GScr_AllocString_t GScr_AllocString = (GScr_AllocString_t)(0x41B12);
typedef bool(__cdecl* W2S)(int localClientNum, Vector3* worldPos, Vector2* outPos);
static W2S WorldToScreenGame = (W2S)(0x45C880); // since this is a different binary i dont think this is going to work, i thought zombie was in the mp one :,( Its ok alteast now I understand more about it lol yup yup, but alloc string is for zombie/campaign one

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

bool Drawer::WorldToScreen(const Vector3* xyzPos, ImVec2* xyPos, const float* matrix, const ImVec2* displaySize) noexcept
{
	xyPos->x = xyzPos->x * matrix[0] + xyzPos->y * matrix[1] + xyzPos->z * matrix[2] + matrix[3];
	xyPos->y = xyzPos->x * matrix[4] + xyzPos->y * matrix[5] + xyzPos->z * matrix[6] + matrix[7];

	float wan = xyzPos->x * matrix[12] + xyzPos->y * matrix[13] + xyzPos->z * matrix[14] + matrix[15];

	if (wan < 0.01f) // is behind me 
		return false;

	ImVec2 NDC{};
	NDC.x = xyPos->x / wan;
	NDC.y = xyPos->y / wan;

	xyPos->x = (displaySize->x  / 2 * NDC.x) + (NDC.x + displaySize->x / 2);
	xyPos->y = -(displaySize->y / 2 * NDC.y) + (NDC.y + displaySize->y / 2);

	return true;
}

void Drawer::Draw(const ImVec2* displaySize) noexcept
{
	using namespace Settings; //nice 
	using namespace SDK;

	
	for (const auto&[address, val] : Hook::entities)
	{
		ImVec2   entPos{};
		Vector3 headPos{};

		// was testing some stuff here so dont mind the junk lol. 
		// its fine im just gonna show you how you get the headpos

		void* Com_GetClientDObj(i, 0); // <- i here is the client number ? 
		if (!dobj)
			continue;
		// no, it's a handle to the entiy, 0 is localclientnum. Since we're only interested of our own client, we always pass 0
		// same with other functions that takes a client num, you always pass 0 to them 
		// So when you say Handle to the entity, you mean the entity address ? 
		// yes, the function is getting the handle to the entity from the ptr passed to the function
		// ooohh ok ok 
		// this needs to be in the loop where you loop through the entities btw
		// do you wanna know how to do bones? I have an idea of how I can do it. You mean bone ESP right ? 
		// yeah, you can use GScr_AllocString for it, to get the bones then I just need to render thoses lines 
		// yeah, u can draw with engine as well if u wanna take it to the next level, not that hard on this engine
		// you can do that after imgui if you wanna extend ur knowledge with the engine and practice reversing as well
		// Using the engine to draw sound like a great idea. I will prolly try to do it after am able to do my features with Imgui.
		// Thx for explaining this me :) 
		// no worries, if there's anything just ask

		// I will :)
		// am cooked

		if (!CG_DObjGetWorldTagPos(&entityPtr /* or w.e u call it*/, dobj, GScr_AllocString("j_head"), headPos))
			continue;

		// now your headpos vector is populated with their headpos 
		// Btw what is exactly DObj, I made the mistake of not using anything that the game use and now kinda lost with the structure of it 

		// DObj = Display object
		// Evertyhing that gets rendered in cod has a DObj, weapons, scavenger packs, cars, killstreaks etc
		// So with this function you can get the pos of all of it, i use this as an example to draw item esp
		// oh alr
		// sounds more clear now lol 

		// so the first function just retrieves the dobj of whatever the entity is from memory, its just an address.
		// other function retrieves the position of the dobj based on the tag name, in this case j_head because that's the head of the dobj
		// you ccan use other tagnames like j_ankle as well, not that its useful but yeah 

		uintptr_t   addressOfEnt = address + 0x104;
		ViewMatrix* viewMatrix = reinterpret_cast<ViewMatrix*>(AViewMatrix);
		Entity*		entity     = reinterpret_cast<Entity*>(addressOfEnt);

		printf("Address : %x\n", addressOfEnt);

		if (!GetBoneOrigin(93, entity, addressOfEnt, &headPos))
			continue;

		printf("Head Pos : x - %f / y - %f / z - %f \n", headPos.x, headPos.y, headPos.z);

		if (!WorldToScreen(&entity->positions, &entPos, viewMatrix->matrix, displaySize))
			continue;

		if (isLinesEnabled)
			Visual::Line(entPos, drawList, displaySize);

		if (isBoxesEnabled)
		{
			ImVec2 screenHeadPos{};
			WorldToScreen(&headPos, &screenHeadPos, viewMatrix->matrix, displaySize);
			Visual::Box(entPos, screenHeadPos, drawList);
		}

		if (isSkeletonsEnabled)
			Visual::Skeleton(drawList);
	}
}