#ifndef NATIVE_H
#define NATIVE_H

#include <stdio.h>
#include <windows.h>

#define NT_SUCCESS(x) ((x) >= 0)
#define SystemProcessInformation 5

#define STATUS_SUCESS               0x00000000
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004


typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           NumberOfThreads;
    ULONG           Reserved1[6];
    LARGE_INTEGER   CreateTime;
    LARGE_INTEGER   UserTime;
    LARGE_INTEGER   KernelTime;
    UNICODE_STRING  ImageName;
    ULONG           BasePriority;
    HANDLE          ProcessId;
    HANDLE          InheriredFromProcessId;
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef NTSTATUS(NTAPI* NtQuerySystemInformation_t)(
    ULONG   SystemInformationClass,
    PVOID   SystemInformation,
    ULONG   SystemInformationLength,
    PULONG  ReturnLength
    );

typedef NTSTATUS(NTSYSCALLAPI* NtALlocateVirtualMemory_t)(
    HANDLE      ProcessHandle,
    PVOID       *BaseAddress,
    ULONG_PTR   ZeroBits,
    PSIZE_T     RegionSize,
    ULONG       AllocationType,
    ULONG       Protect
    );

typedef NTSTATUS(NTSYSCALLAPI* NtOpenProcess_t)(
    PHANDLE             ProcessHandle,
    ACCESS_MASK         DesiredAccess,
    POBJECT_ATTRIBUTES  ObjectAttributes,
    PCLIENT_ID          ClientId
    );

#endif //NATIVE_H
