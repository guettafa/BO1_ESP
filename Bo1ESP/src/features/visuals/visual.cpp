#include "visuals/visual.h"

void Visual::Line(const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize) noexcept
{
	ImGui::Text("W2S - x : %f y : %f", xyPos.x, xyPos.y);
	drawList->AddLine(ImVec2(displaySize->x / 2, displaySize->y), xyPos, IM_COL32(255, 255, 255, 255), 0.5f);
}

void Visual::Box(const ImVec2 xyPos, const ImVec2 headPos, ImDrawList* drawList) noexcept
{
	auto bottomLeft = ImVec2(xyPos.x - 30,  xyPos.y);
	auto topRight   = ImVec2(xyPos.x + 70, xyPos.y - 140);
	
	drawList->AddRect(bottomLeft, topRight, IM_COL32(255, 255, 255, 255), 0.0f, ImDrawFlags_None, 0.5f);
}

void Visual::Skeleton(ImDrawList* drawList) noexcept
{
	// draw skeleton
}
