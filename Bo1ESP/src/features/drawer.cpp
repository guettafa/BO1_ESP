#include "drawer.h"

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

ImVec2 Drawer::WorldToScreen(Vector3 xyzPos) noexcept
{
	return ImVec2();
}

void Drawer::Draw(const ImVec2* displaySize) noexcept
{
	using namespace Settings;

	if (isLinesEnabled)
	{
		Visual::Line(ImVec2(displaySize->x / 2, displaySize->y / 2), drawList, displaySize);
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