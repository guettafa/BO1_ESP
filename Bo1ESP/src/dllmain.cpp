#include "pch.h"
#include "client.h"
#include "hook.h"

#pragma warning(disable: 4996)

typedef void(__cdecl* tCodeCave)();
tCodeCave pReturnBack = nullptr;

void HookFunc()
{
    std::printf("HOOKED \n");
    pReturnBack();
}

bool MainThread(HMODULE hModule)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    const uintptr_t address       = Client::FindPattern(L"BlackOps.exe", Client::pattern, 53);
    const uintptr_t codeCaveAddrs = Trampoline((char*)address, (char*)&HookFunc, 8);

#ifdef _DEBUG
    std::printf("address : %x\naddress of codecave : %x\naddress of function : %x", address, codeCaveAddrs, &HookFunc);
#endif

    // codeCaveInstruction refer now to a function that contain all instructions in the code cave
    pReturnBack = (tCodeCave)codeCaveAddrs;

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
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) MainThread, hModule, 0, nullptr);
    }
    return TRUE;
}

