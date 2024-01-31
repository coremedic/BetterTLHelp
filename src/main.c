#include "Native.h"



HANDLE CreateToolHelp32SnapshotH(DWORD dwFlags, DWORD dwPid) {

}


int main() {
    HMODULE                     hNtDll                      = NULL;
    NtQuerySystemInformation_t  fnpNtQuerySystemInformation = NULL;
    PVOID                       pBuffer                     = NULL;
    ULONG                       cbBuffer                    = 131072;
    HANDLE                      hHeap                       = NULL;
    NTSTATUS                    ntStatus                    = NULL;
    INT                         retStatus                   = -1;
    PSYSTEM_PROCESS_INFORMATION pSysProcInfo;

    hNtDll = GetModuleHandleA("ntdll.dll");
    if (hNtDll == INVALID_HANDLE_VALUE) {
        printf("[!] GetModuleHandleA failed with error: %lu [%d]\n", GetLastError(), __LINE__);
        goto _CLEAN_UP;
    }

    fnpNtQuerySystemInformation = (NtQuerySystemInformation_t)GetProcAddress(hNtDll, "NtQuerySystemInformation");
    if (!fnpNtQuerySystemInformation) {
        printf("[!] GetProcAddress failed with error: %lu [%d]\n", GetLastError(), __LINE__);
        goto _CLEAN_UP;
    }

    hHeap = GetProcessHeap();
    if (hHeap == INVALID_HANDLE_VALUE) {
        printf("[!] GetProcessHeap failed with error: %lu [%d]\n", GetLastError(), __LINE__);
        goto _CLEAN_UP;
    }

    while (TRUE) {
        pBuffer = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbBuffer);
        if (!pBuffer) {
            printf("[!] HeapAlloc failed with error: %lu [%d]\n", GetLastError(), __LINE__);
            goto _CLEAN_UP;
        }

        ntStatus = fnpNtQuerySystemInformation(SystemProcessInformation, pBuffer, cbBuffer, &cbBuffer);
        if (ntStatus == STATUS_INFO_LENGTH_MISMATCH) {
            printf("[i] NtQuerySystemInformation failed with error: STATUS_INFO_LENGTH_MISMATCH, increasing buffer size...\n");
            HeapFree(hHeap, NULL, pBuffer);
            printf("[i] Current buffer size is: %lu bytes\n", cbBuffer);
            cbBuffer *= 2;
        } else if (!NT_SUCCESS(ntStatus)) {
            printf("[!] NtQuerySystemInformation failed with error: %#010x [%d]\n", ntStatus, __LINE__);
            goto _CLEAN_UP;
        } else {
            break;
        }
    }

    pSysProcInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
    while (pSysProcInfo->NextEntryOffset) {
        printf("\nProcess: %ls | PID: %d\n", pSysProcInfo->ImageName.Buffer, pSysProcInfo->ProcessId);
        pSysProcInfo = (PSYSTEM_PROCESS_INFORMATION)((LPBYTE)pSysProcInfo + pSysProcInfo->NextEntryOffset);
    }

    retStatus = 0;

    _CLEAN_UP:
    if (pBuffer) HeapFree(GetProcessHeap(), NULL, pBuffer);
    if (hNtDll) CloseHandle(hNtDll);
    return retStatus;
}