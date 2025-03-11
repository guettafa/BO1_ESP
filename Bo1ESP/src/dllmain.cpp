
#include "pch.h"
#include "client.h"
#include "hook.h"
#include "game.h"
#include <iostream>

#pragma warning(disable: 4996)

VOID CreateConsole()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
}

BOOL WINAPI MainThread(HMODULE hModule)
{
    using namespace Hook;

    CreateConsole();

    //69E7B4C0
    // GameOverlayRenderer.dll offset Present function hook : 0x6B4C0
    //const uintptr_t d3d9PresentFunctionAddrs = (uintptr_t)GetModuleHandle(L"GameOverlayRenderer.dll") + (uintptr_t)0x6B4C0;

    const uintptr_t hookEntityAddrs = Client::FindPattern(L"BlackOps.exe", Client::entityInstructionPattern, 53);
    const uintptr_t d3d9PresentFunctionAddrs  = (uintptr_t)GetModuleHandle(L"d3d9.dll") + (uintptr_t)Game::Offsets::d3d9PresentFunctionOffsets;
    const uintptr_t d3d9EndSceneFunctionAddrs = (uintptr_t)GetModuleHandle(L"d3d9.dll") + (uintptr_t)Game::Offsets::d3d9EndSceneFunctionOffsets;

    printf("functioin addrs : %x\n", d3d9PresentFunctionAddrs);

    codeCaveAddrs    = Trampoline((char*)hookEntityAddrs, (char*)&EntityHook, 8);
    originalEndScene = (EndScene)Trampoline((char*)d3d9EndSceneFunctionAddrs, (char*)&EndSceneHook, 7);
    //originalPresent  = (Present)Trampoline((char*)d3d9PresentFunctionAddrs, (char*)&PresentHook, 5);

    while (true)
    {
        if (GetAsyncKeyState(VK_DOWN))
            break;
    }

    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    }
    return TRUE;
}

