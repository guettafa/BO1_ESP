#pragma once

#include "settings.h"

namespace Visual
{
	ImVec2 WorldToScreen(float x, float y, float z);

	void Line	 (const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize);
	void Box	 (ImDrawList* drawList);
	void Skeleton(ImDrawList* drawList);
}