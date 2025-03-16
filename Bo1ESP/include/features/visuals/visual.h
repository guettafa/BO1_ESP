#pragma once

#include <math.h>
#include "settings.h"

namespace Visual
{
	void Line	  (const ImVec2 xyPos, ImDrawList* drawList, const ImVec2* displaySize) noexcept;
	void Box	  (const ImVec2 xyPos, const ImVec2 headPos, ImDrawList* drawList)      noexcept;
	void Skeleton (ImDrawList* drawList)												noexcept;
}