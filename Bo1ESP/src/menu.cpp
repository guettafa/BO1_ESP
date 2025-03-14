#include "menu.h"

namespace Menu
{
	HWND  hWnd				 = nullptr;
	ImDrawList* drawList	 = nullptr;
	bool  isImguiInitialized = false;
	bool  isMenuOpen		 = true;
}

VOID Menu::InitImGui(IDirect3DDevice9* pDevice)
{
	if (isImguiInitialized) return;

	hWnd = GetForegroundWindow();

	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
	
	isImguiInitialized = true;
}

VOID Menu::RenderMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.MouseDrawCursor = isMenuOpen;
	io.WantCaptureMouse = true;

	io.MouseDown[0] = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	io.MouseDown[1] = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;

	ImGui::NewFrame();
	if (isMenuOpen)
	{
		// Render Menu

		ImGui::Begin("marfield & gario");
		{
			ImGui::Text("FPS : %.2f", io.Framerate);
			ImGui::Text("Mouse Data: x - %f / y - %f", io.MousePos.x, io.MousePos.y);
			ImGui::Text("Capture : %d", io.WantCaptureMouse);
			ImGui::Text("Hello B01");
		}
		ImGui::End();
	}

	// Render ESP
	
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImGui::Begin("drawables", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		drawList = ImGui::GetWindowDrawList();
		drawList->AddLine(ImVec2(1920 / 2, 1080), ImVec2(1920/2, 1080/2), IM_COL32(255, 255, 255, 255), 0.5f);
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

	isImguiInitialized = FALSE;
}