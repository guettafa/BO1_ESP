#pragma once

#include "visuals/visual.h"
#include "settings.h"

namespace Drawer
{
	extern ImDrawList* drawList;

	void Draw(const ImVec2* diplaySize) noexcept;
}