#include "client.h"
#include "trampoline.h"
#include "hook.h"
#include "game.h"
#include "menu.h"

VOID CreateConsole()
{
    AllocConsole();
    FILE* file;
    freopen_s(&file,"CONOUT$", "w", stdout);
}

BOOL WINAPI MainThread(HMODULE hModule)
{
    using namespace Hook;

    CreateConsole();

    const uintptr_t hookEntityAddrs           = Client::FindPattern(L"BlackOps.exe", Client::entityInstructionPattern, 53);
    const uintptr_t d3d9EndSceneFunctionAddrs = (uintptr_t)GetModuleHandle(L"d3d9.dll") + (uintptr_t)Game::RVA::d3d9EndSceneFunction;

#pragma region Placing Hooks

    codeCave         =            Trampoline((char*)hookEntityAddrs,           (char*)&EntityHook,   8);
    originalEndScene = (EndScene) Trampoline((char*)d3d9EndSceneFunctionAddrs, (char*)&EndSceneHook, 7);

#pragma endregion

    while (true)
    {
        if (GetAsyncKeyState(VK_HOME) & 0x01)
        {
            Menu::isMenuOpen = !Menu::isMenuOpen;
        }

        if (GetAsyncKeyState(VK_END))
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

