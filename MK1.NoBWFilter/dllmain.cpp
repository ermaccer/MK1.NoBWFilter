// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "utils/addr.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"

using namespace Memory::VP;
using namespace hook::txn;

void Init()
{
    static uintptr_t pat = 0;

    pat = (uintptr_t)get_pattern("F3 0F 11 8F 94 04 00 00");

    if (pat)
        Memory::VP::Nop(pat, 8);
    else
        MessageBoxA(0, "Failed to find required code pattern!\n\nGame or plugin needs updating.", "MK1.NoBWFilter", MB_ICONERROR);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

