#include "client.h"
#include "trampoline.h"
#include "hook.h"
#include "game.h"
#include "menu.h"

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

    const uintptr_t hookEntityAddrs           = Client::FindPattern(L"BlackOps.exe", Client::entityInstructionPattern, 53);
    const uintptr_t d3d9EndSceneFunctionAddrs = (uintptr_t)GetModuleHandle(L"d3d9.dll") + (uintptr_t)Game::Offsets::d3d9EndSceneFunctionRVA;

#pragma region Placing Hooks

    codeCave         =            Trampoline((char*)hookEntityAddrs,           (char*)&EntityHook,   8);
    originalEndScene = (EndScene) Trampoline((char*)d3d9EndSceneFunctionAddrs, (char*)&EndSceneHook, 7);

#pragma endregion

    while (true)
    {
        if (GetAsyncKeyState(VK_HOME) & 0x01)
        {
            Menu::g_isMenuOpen = !Menu::g_isMenuOpen;
        }

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

