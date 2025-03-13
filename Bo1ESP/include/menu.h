#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <windows.h>
#include <iostream>

namespace Menu
{
	extern HWND g_hWnd;
	extern BOOL g_imguiInitialized;
	extern BOOL g_isMenuOpen;

	VOID InitImGui(IDirect3DDevice9* pDevice);
	VOID RenderMenu();
	VOID Cleanup();
}