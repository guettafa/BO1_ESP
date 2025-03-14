#pragma once

#include <imgui.h>

namespace Visual
{
	ImVec2 WorldToScreen(float x, float y, float z);

	void Line	 (ImVec2 xyPos, ImDrawList* drawList);
	void Box	 (ImDrawList* drawList);
	void Skeleton(ImDrawList* drawList);
}