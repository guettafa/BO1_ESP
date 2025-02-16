#include "pch.h"
#include "client.h"
#include "hook.h"

#pragma warning(disable: 4996)

using CodeCave = void(_cdecl*)();
CodeCave codeCaveInstruction;

void HookFunction()
{
    std::printf("HOOKED \n");
    codeCaveInstruction();
}

bool MainThread(HMODULE hModule)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    const uintptr_t address       = Client::FindPattern (L"BlackOps.exe", Client::pattern, 53);
    const uintptr_t codeCaveAddrs =         Trampoline  ((char*)address, (char*)&HookFunction, 8);

#ifdef _DEBUG
    std::printf("address : %x\naddress of codecave : %x\n", address, codeCaveAddrs);
#endif

    // codeCaveInstruction refer now to a function that contain all instructions in the code cave
    codeCaveInstruction = (CodeCave)codeCaveAddrs;
    
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
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) MainThread, hModule, 0, nullptr));
    }
    return TRUE;
}

