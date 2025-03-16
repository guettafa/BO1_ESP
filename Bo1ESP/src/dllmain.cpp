#include "pattern.h"
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

    const uintptr_t AHookEntity           = Pattern::FindPattern(L"BlackOps.exe", Pattern::PEntityInstruction, 53);
    const uintptr_t AD3d9EndSceneFunction = (uintptr_t)GetModuleHandle(L"d3d9.dll") + (uintptr_t)Game::RVA::RVAd3d9EndSceneFunction;

#pragma region Placing Hooks

    ACodeCave         =            Trampoline((char*)AHookEntity,           (char*)&EntityHook,   8);
    AOriginalEndScene = (EndScene) Trampoline((char*)AD3d9EndSceneFunction, (char*)&EndSceneHook, 7);

#pragma endregion

    while (true)
    {
        if (GetAsyncKeyState(VK_HOME) & 0x01)
            Menu::isMenuOpen = !Menu::isMenuOpen;

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

