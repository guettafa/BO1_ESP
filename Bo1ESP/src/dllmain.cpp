#include "memory.h"
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
    using Menu::isMenuOpen;

    CreateConsole();

    const uintptr_t AHookEntity           = FindPattern(L"BlackOps.exe", PEntityInstruction, 53);
    const uintptr_t AD3d9EndSceneFunction = (uintptr_t)GetModuleHandle(L"d3d9.dll") + (uintptr_t)SDK::Addresses::RVAD3d9EndSceneFunction;

#pragma  region GameRelated

    for (auto& bone : SDK::bones)
    {
        bone.id = SDK::RegisterTag(bone.name, 0);
        std::printf("Bone ID : %d\n", bone.id);
    }

#pragma endregion

#pragma region Placing Hooks

    ACodeCave =            Trampoline((char*)AHookEntity,           (char*)&EntityHook,   8);
    OEndScene = (EndScene) Trampoline((char*)AD3d9EndSceneFunction, (char*)&EndSceneHook, 7);

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

