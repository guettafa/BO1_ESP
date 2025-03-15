#pragma once

#include "settings.h"

namespace Visual
{
	void Line	 (const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize) noexcept;
	void Box	 (ImDrawList* drawList)												   noexcept;
	void Skeleton(ImDrawList* drawList)												   noexcept;
}