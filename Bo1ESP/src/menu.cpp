#include "menu.h"

namespace Menu
{
	HWND		hWnd			   = nullptr;
	bool		isImguiInitialized = false;
	bool		isMenuOpen		   = true;
}

VOID Menu::Init(IDirect3DDevice9* pDevice)
{
	if (isImguiInitialized) return;

	hWnd = GetForegroundWindow();

	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
	
	isImguiInitialized = true;
}

VOID Menu::Render()
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

			ImGui::Separator();

			ImGui::Checkbox("Lines",     &Settings::isLinesEnabled);
			ImGui::Checkbox("Boxes",     &Settings::isBoxesEnabled);
			ImGui::Checkbox("Skeletons", &Settings::isSkeletonsEnabled);
		}
		ImGui::End();
	}

	// Render Visuals
	
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Visuals", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		Drawer::drawList = ImGui::GetWindowDrawList();
		Drawer::Draw();
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

	isImguiInitialized = false;
}