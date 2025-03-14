#pragma once

#include <imgui.h>

struct Drawable
{
private:
	ImDrawList* drawList;

public:
	Drawable() : drawList(ImGui::GetWindowDrawList()) {}

	void Line	 (ImVec2 xyPos) noexcept;
	void Box	 ()				noexcept;
	void Skeleton()				noexcept;
};