#pragma once

#include "visuals/visual.h"
#include "settings.h"
#include "types.h"

#include "hook.h"

namespace Drawer
{
	extern ImDrawList* drawList;

	bool   WorldToScreen (const Vector3* xyzPos, Vector2* xyPos, const float* matrix, const ImVec2* displaySize) noexcept;
	void   Draw			 (const ImVec2* displaySize)																	noexcept;
}