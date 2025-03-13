#include "menu.h"

namespace Menu
{
	HWND g_hWnd				= nullptr;
	BOOL g_imguiInitialized = FALSE;
	BOOL g_isMenuOpen		= TRUE;
}

VOID Menu::InitImGui(IDirect3DDevice9* pDevice)
{
	if (g_imguiInitialized) return;

	g_hWnd = FindWindow(NULL, L"BlackOps.exe");

	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(pDevice);
	
	g_imguiInitialized = TRUE;
}

VOID Menu::RenderMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	std::cout << "ON RENDER" << std::endl;

	ImGui::Begin("Hello, world!");
	{
		ImGui::SetWindowSize({ 500, 300 }, ImGuiCond_Once);

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