#include "Native.h"

int main() {
    HMODULE                     hNtDll                      = NULL;
    tNtQuerySystemInformation   fnpNtQuerySystemInformation = NULL;
    PVOID                       buffer                      = NULL;
    NTSTATUS                    ntStatus                    = NULL;
    INT                         retStatus                   = -1;
    PSYSTEM_PROCESS_INFORMATION pSysProcInfo;


    buffer = VirtualAlloc(NULL, 1024^2, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!buffer) {
        printf("[!] VirtualAlloc failed with error: %lu [%d]\n", GetLastError(), __LINE__);
        return -1;
    }

    getchar();

    pSysProcInfo = (PSYSTEM_PROCESS_INFORMATION)buffer;

    hNtDll = GetModuleHandleA("ntdll.dll");
    if (hNtDll == INVALID_HANDLE_VALUE) {
        printf("[!] GetModuleHandleA failed with error: %lu [%d]\n", GetLastError(), __LINE__);
        goto _CLEAN_UP;
    }

    fnpNtQuerySystemInformation = (tNtQuerySystemInformation)GetProcAddress(hNtDll, "NtQuerySystemInformation");
    if (!fnpNtQuerySystemInformation) {
        printf("[!] GetProcAddress failed with error: %lu [%d]\n", GetLastError(), __LINE__);
        goto _CLEAN_UP;
    }

    if (!NT_SUCCESS(ntStatus = fnpNtQuerySystemInformation(SystemProcessInformation, pSysProcInfo, sizeof(buffer), NULL))) {
        printf("[!] NtQuerySystemInformation failed with error: %lu [%d]\n", ntStatus, __LINE__);
        //goto _CLEAN_UP;
    }

    while (pSysProcInfo->NextEntryOffset) {
        printf("\nProcess: %ws | PID: %d\n", pSysProcInfo->ImageName.Buffer, pSysProcInfo->ProcessId);
        pSysProcInfo = (PSYSTEM_PROCESS_INFORMATION)((LPBYTE)pSysProcInfo + pSysProcInfo->NextEntryOffset);
    }

    retStatus = 0;

    _CLEAN_UP:
    if (buffer) VirtualFree(buffer, 0, MEM_RELEASE);
    if (hNtDll) CloseHandle(hNtDll);
    return retStatus;
}