#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <windows.h>
#include <iostream>

#include "drawer.h"

namespace Menu
{
	extern HWND      hWnd;
	extern bool      isImguiInitialized;
	extern bool      isMenuOpen;

	VOID Init(IDirect3DDevice9* pDevice);
	VOID Render();
	VOID Cleanup();
}