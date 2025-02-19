#include "pch.h"
#include "client.h"
#include "hook.h"
#include <iostream>

#pragma warning(disable: 4996)

uintptr_t codeCaveAddrs;
uintptr_t entityAddrs = 0;

uintptr_t localPlayerEntityAddrs = 0x1a796f8;

std::vector<uintptr_t> entities{};
bool isAlreadyHere = false;

__declspec(naked) void HookFunc()
{
    std::printf("HOOKED \n");

    _asm
    {
        mov [entityAddrs],esi
    }

    if (entityAddrs != localPlayerEntityAddrs)
    {
        for (uintptr_t entity : entities)
        {
            if (entityAddrs != entity)
                continue;

            isAlreadyHere = true; 
            std::printf(" Entity is already here: %x\n", entityAddrs);

        }

        if (!isAlreadyHere)
        {
            entities.push_back(entityAddrs);
            isAlreadyHere = false;
        }
        std::printf("Size of vector : %d\n", entities.size());
    }

    _asm
    {
        jmp [codeCaveAddrs]
    }
}

BOOL WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    freopen("CONOUT$","w", stdout);

    const uintptr_t address = Client::FindPattern(L"BlackOps.exe", Client::pattern, 53);
    codeCaveAddrs = Trampoline((char*)address, (char*)&HookFunc, 8);

#ifdef _DEBUG
    std::printf("address : %x\naddress of codecave : %x\n", address, codeCaveAddrs);
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

