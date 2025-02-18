#include "pch.h"
#include "client.h"
#include "hook.h"
#include <iostream>

#pragma warning(disable: 4996)

typedef void(__cdecl* tCodeCave)();
tCodeCave pReturnBack = nullptr;

void HookFunc()
{
    std::printf("HOOKED \n");
    pReturnBack();
}

BOOL WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    freopen("CONOUT$","w", stdout);

    const uintptr_t address = Client::FindPattern(L"BlackOps.exe", Client::pattern, 53);
    const uintptr_t codeCaveAddrs = Trampoline((char*)address, (char*)&HookFunc, 8);

#ifdef _DEBUG
    std::printf("address : %x\naddress of codecave : %x\n", address, codeCaveAddrs);
#endif

    pReturnBack = (tCodeCave)codeCaveAddrs;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
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

