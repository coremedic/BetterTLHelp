#include "Native.h"

int main() {
    HMODULE                     hNtDll                      = NULL;
    tNtQuerySystemInformation   fnpNtQuerySystemInformation = NULL;

    hNtDll = GetModuleHandleA("ntdll.dll");
    if (!hNtDll) return 1;

    fnpNtQuerySystemInformation = (tNtQuerySystemInformation)GetProcAddress(hNtDll, "NtQuerySystemInformation");
    if (!fnpNtQuerySystemInformation) return 1;

    return 0;
}