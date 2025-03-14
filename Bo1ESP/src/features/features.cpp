#include "drawable.h"

ImVec2 WorldToScreen(float x, float y, float z) noexcept
{
	return ImVec2(x, y);
}

void Drawable::Line(ImVec2 xyPos) noexcept
{
	drawList->AddLine(ImVec2(1920 / 2, 1080), xyPos, IM_COL32(255, 255, 255, 255), 0.5f);
}

void Drawable::Box() noexcept
{
	// Draw a box
}

void Drawable::Skeleton() noexcept
{
	// Draw Skeleton
}
