#pragma once

#include "settings.h"

namespace Visual
{
	ImVec2 WorldToScreen(float x, float y, float z)									   noexcept;

	void Line	 (const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize) noexcept;
	void Box	 (ImDrawList* drawList)												   noexcept;
	void Skeleton(ImDrawList* drawList)												   noexcept;
}