#include "menu.h"

namespace Menu
{
	HWND  g_hWnd		     = nullptr;
	bool  g_imguiInitialized = false;
	bool  g_isMenuOpen		 = true;
}

VOID Menu::InitImGui(IDirect3DDevice9* pDevice)
{
	if (g_imguiInitialized) return;

	g_hWnd = GetForegroundWindow();

	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(pDevice);
	
	g_imguiInitialized = true;
}

VOID Menu::RenderMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.MouseDrawCursor = g_isMenuOpen;

	io.MouseDown[0] = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	io.MouseDown[1] = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;

	if (!g_isMenuOpen) return;

	ImGui::NewFrame();
	ImGui::Begin("Hello, world!");
	{
		ImGui::Text("Mouse Data: x - %f / y - %f", io.MousePos.x, io.MousePos.y);
		ImGui::Text("Capture : %d", io.WantCaptureMouse);
		ImGui::Text("Hello B01");
	}
	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

VOID Menu::Cleanup()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	g_imguiInitialized = FALSE;
}