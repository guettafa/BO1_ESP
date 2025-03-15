#include "visuals/visual.h"

ImVec2 Visual::WorldToScreen(float x, float y, float z)
{
	return ImVec2();
}

void Visual::Line(const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize)
{
	drawList->AddLine(ImVec2(displaySize->x / 2, displaySize->y), xyPos, IM_COL32(255, 255, 255, 255), 0.5f);
}

void Visual::Box(ImDrawList* drawList)
{
	// draw box
}

void Visual::Skeleton(ImDrawList* drawList)
{
	// draw skeleton
}
