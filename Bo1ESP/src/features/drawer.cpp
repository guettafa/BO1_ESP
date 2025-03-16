#include "drawer.h"

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

bool Drawer::WorldToScreen(const Vector3* xyzPos, Vector2* xyPos, const float matrix[16]) noexcept
{
	xyPos->x = xyzPos->x * matrix[0] + xyzPos->y * matrix[1] + xyzPos->z * matrix[2] + matrix[3];
	xyPos->y = xyzPos->x * matrix[4] + xyzPos->y * matrix[5] + xyzPos->z * matrix[6] + matrix[7];

	float wan = xyzPos->x * matrix[12] + xyzPos->y * matrix[13] + xyzPos->z * matrix[14] + matrix[15];

	//// in my back
	//if (wan < 0.01f)
	//	return false;

	ImVec2 NDC;
	NDC.x = xyPos->x / wan;
	NDC.y = xyPos->y / wan;

	xyPos->x = (2560 / 2 * NDC.x) + (NDC.x + 2560 / 2);
	xyPos->y = -(1440/ 2 * NDC.y) + (NDC.y + 1440 / 2);

	return true;
}

void Drawer::Draw(ImVec2 displaySize) noexcept
{
	using namespace Settings;

	for (auto& _entity : Hook::entities)
	{
		Vector2 xyPos;
		Game::Entity* entity = reinterpret_cast<Game::Entity*>(_entity.first);
		ViewMatrix* viewMatrix = reinterpret_cast<ViewMatrix*>(Game::AViewMatrix);
		
		WorldToScreen(&entity->positions, &xyPos, viewMatrix->Matrix);

		if (isLinesEnabled)
		{
			ImGui::Text("X: %f Y: %f Z: %f", entity->positions.x, entity->positions.y, entity->positions.z);
			Visual::Line(ImVec2(xyPos.x, xyPos.y), drawList, &displaySize);
		}

		if (isBoxesEnabled)
		{
			// draw boxes on each entity
			Visual::Box(drawList);
		}

		if (isSkeletonsEnabled)
		{
			// draw skeleton on each entity
			Visual::Skeleton(drawList);
		}
	}
}