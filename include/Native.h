#ifndef NATIVE_H
#define NATIVE_H

#include <windows.h>

typedef NTSTATUS(NTAPI* tNtQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

#endif //NATIVE_H
