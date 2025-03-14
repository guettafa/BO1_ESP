#include "drawer.h"

namespace Drawer
{
	ImDrawList* drawList = nullptr;
}

void Drawer::Draw()
{
	if (Settings::isLinesEnabled)
	{
		// draw lines on each entity
		Visual::Line(ImVec2(1920 / 2, 1080 / 2), drawList);
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