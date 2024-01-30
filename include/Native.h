#ifndef NATIVE_H
#define NATIVE_H

#include <windows.h>

typedef NTSTATUS(WINAPI *t_NtQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

#endif //NATIVE_H
