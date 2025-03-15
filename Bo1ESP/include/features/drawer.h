#pragma once

#include "visuals/visual.h"
#include "settings.h"
#include "types.h"

namespace Drawer
{
	extern ImDrawList* drawList;

	ImVec2 WorldToScreen (Vector3 xyzPos) noexcept;
	void   Draw			 (const ImVec2* diplaySize) noexcept;
}