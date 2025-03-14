#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <windows.h>
#include <iostream>

#include "drawable.h"

namespace Menu
{
	extern HWND      hWnd;
	//extern Drawable drawer;
	extern ImDrawList* drawList;
	extern bool      isImguiInitialized;
	extern bool      isMenuOpen;

	VOID InitImGui(IDirect3DDevice9* pDevice);
	VOID RenderMenu();
	VOID Cleanup();
}