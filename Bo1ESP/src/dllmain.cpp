#include <iostream>

#include "pch.h"
#include "client.h"
#include "hook.h"
#include <d3d9.h>
#include <dxgi.h>

#pragma warning(disable: 4996)

using PresentHook = HRESULT(__stdcall*)(IDXGISwapChain* pSwapchain, UINT syncInterval, UINT flags);
PresentHook PresentFunc = nullptr;

BOOL WINAPI MainThread(HMODULE hModule)
{
    using namespace Hook;

    AllocConsole();
    freopen("CONOUT$","w", stdout);

    const uintptr_t hookEntityAddrs = Client::FindPattern(L"BlackOps.exe", Client::entityInstructionPattern, 53);
    const uintptr_t dxgiPresentFunctionAddrs = (uintptr_t)GetModuleHandle(L"dxgi.dll") + (uintptr_t)0xA4810;

    codeCaveAddrs = Trampoline((char*)hookEntityAddrs, (char*)&EntityHook, 8);

#ifdef _DEBUG
    std::printf("address : %x\naddress of codecave : %x\n address of dxgi present : %x\n", hookEntityAddrs, codeCaveAddrs, dxgiPresentFunctionAddrs);
#endif

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

