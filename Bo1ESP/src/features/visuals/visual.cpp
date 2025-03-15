#include "visuals/visual.h"

void Visual::Line(const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize) noexcept
{
	drawList->AddLine(ImVec2(displaySize->x / 2, displaySize->y), xyPos, IM_COL32(255, 255, 255, 255), 0.5f);
}

void Visual::Box(ImDrawList* drawList) noexcept
{
	// draw box
}

void Visual::Skeleton(ImDrawList* drawList) noexcept
{
	// draw skeleton
}
