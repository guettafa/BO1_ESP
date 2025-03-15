#include "drawer.h"

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

void Drawer::Draw(const ImVec2* displaySize)
{
	if (Settings::isLinesEnabled)
	{
		Visual::Line(ImVec2(displaySize->x / 2, displaySize->y / 2), drawList, displaySize);
	}

	if (Settings::isBoxesEnabled)
	{
		// draw boxes on each entity
		Visual::Box(drawList);
	}

	if (Settings::isSkeletonsEnabled)
	{
		// draw skeleton on each entity
		Visual::Skeleton(drawList);
	}
}