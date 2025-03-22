#include "drawer.h"

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

bool Drawer::WorldToScreen(const Vector3* xyzPos, ImVec2* xyPos, const float* matrix, const ImVec2* displaySize) noexcept
{
	xyPos->x = xyzPos->x * matrix[0] + xyzPos->y * matrix[1] + xyzPos->z * matrix[2] + matrix[3];
	xyPos->y = xyzPos->x * matrix[4] + xyzPos->y * matrix[5] + xyzPos->z * matrix[6] + matrix[7];

	float wan = xyzPos->x * matrix[12] + xyzPos->y * matrix[13] + xyzPos->z * matrix[14] + matrix[15];

	if (wan < 0.01f) // us behind me 
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
	using namespace Settings;
	using Hook::GetTagPos, Hook::OGetTagPos;
	using SDK::AViewMatrix,SDK::Entity;

	for (const auto&[addressOfEnt, val] : Hook::entities)
	{
		ImVec2      entPos{};
		ViewMatrix* viewMatrix = reinterpret_cast<ViewMatrix*>(AViewMatrix);
		Entity*		entity     = reinterpret_cast<Entity*>(addressOfEnt);

		Vector3 headPos{};
		void* mesh = nullptr;
		OGetTagPos(entity, mesh, 2, headPos);

		// Drawing

		if (!WorldToScreen(&entity->positions, &entPos, viewMatrix->matrix, displaySize))
			continue;

		if (isLinesEnabled)
			Visual::Line(entPos, drawList, displaySize);

		if (isBoxesEnabled)
		{
			ImGui::Text("Head Origin - x: %f, y: %f, z: %f", headPos.x, headPos.y, headPos.z);

			ImVec2 headPos{};
			Visual::Box(entPos, headPos, drawList);
		}

		if (isSkeletonsEnabled)
			Visual::Skeleton(drawList);
	}
}