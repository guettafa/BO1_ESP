#include "drawer.h"

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

void ConvertToRange(ImVec2* xyPos)
{
	xyPos->x /= 1920.0f;
	xyPos->x *= 2.0f;
	xyPos->x -= 1.0f;
	
	xyPos->y /= 1080.0f;
	xyPos->y *= 2.0f;
	xyPos->y -= 1.0f;
}

bool Drawer::WorldToScreen(const Vector3* xyzPos, ImVec2* xyPos, const float* matrix) noexcept
{
	xyPos->x = xyzPos->x * matrix[0] + xyzPos->y * matrix[1] + xyzPos->z * matrix[2] + matrix[3];
	xyPos->y = xyzPos->x * matrix[4] + xyzPos->y * matrix[5] + xyzPos->z * matrix[6] + matrix[7];

	float wan = xyzPos->x * matrix[12] + xyzPos->y * matrix[13] + xyzPos->z * matrix[14] + matrix[15];
	
	// in my back
	if (wan < 0.01f)
		return false;

	ImVec2 ndc;
	ndc.x = xyPos->x / wan;
	ndc.y = xyPos->y / wan;

	xyPos->x = (1920 / 2 * ndc.x) + (ndc.x + 1920 / 2);
	xyPos->y = (1080 / 2 * ndc.y) + (ndc.y + 1080 / 2);

	xyPos->x /= 1920.0f;
	xyPos->x *= 2.0f;
	xyPos->x -= 1.0f;

	xyPos->y /= 1080.0f;
	xyPos->y *= 2.0f;
	xyPos->y -= 1.0f;

	return true;
}

void Drawer::Draw(ImVec2* displaySize) noexcept
{
	using namespace Settings;

	for (auto& _entity : Hook::entities)
	{
		ImVec2 xyPos;
		Game::Entity* entity = reinterpret_cast<Game::Entity*>(_entity.first);
		ViewMatrix* viewMatrix = reinterpret_cast<ViewMatrix*>(Game::AViewMatrix);
		
		WorldToScreen(&(entity->positions), &xyPos, viewMatrix->Matrix);

		if (isLinesEnabled)
		{
			Visual::Line(xyPos, drawList, displaySize);
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