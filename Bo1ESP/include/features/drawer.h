#pragma once

#include "visuals/visual.h"
#include "settings.h"
#include "types.h"

#include "hook.h"

namespace Drawer
{
	extern ImDrawList* drawList;

	bool   WorldToScreen(const Vector3* xyzPos, Vector2* xyPos, const float matrix[16]) noexcept;
	void   Draw			 (ImVec2 diplaySize) noexcept;
}