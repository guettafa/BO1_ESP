#include "hook.h"
#include "game.h"
#include "menu.h"
#include <iostream>

bool testInit = false;

namespace Hook
{
	EndScene originalEndScene = nullptr;

	std::unordered_map<uintptr_t, bool> entities{};
	uintptr_t entityAddrs			 = 0;
	uintptr_t xPosOfEntAddrs		 = 0;
	uintptr_t codeCave			     = 0;

	float* xPosOfEnt = nullptr;
}

HRESULT __stdcall Hook::EndSceneHook(IDirect3DDevice9* pDevice)
{
	//Menu::InitImGui(pDevice);
	//Menu::RenderMenu();

	if (!testInit)
	{
		HWND g_hWnd = GetForegroundWindow();

		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(g_hWnd);
		ImGui_ImplDX9_Init(pDevice);
		testInit = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");
	{
		ImGui::Text("Hello B01");
	}
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
	return originalEndScene(pDevice);
}

NAKED void Hook::EntityHook()
{
	__asm
	{
		mov[entityAddrs], esi
	}

	if (!entities[entityAddrs] && entityAddrs != Game::localPlayerEntityAddrs)
		entities[entityAddrs] += 1;

	xPosOfEnt = reinterpret_cast<float*>(entityAddrs + 0x18);

	std::printf("size   : %d\n", entities.size());
	std::printf("xpos   : %f\n", *xPosOfEnt);

	__asm
	{
		jmp[codeCave]
	}
}
