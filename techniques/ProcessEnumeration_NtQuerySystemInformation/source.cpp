// Source: http://www.rohitab.com/discuss/topic/40504-using-ntquerysysteminformation-to-get-process-list/
// Author: zwclose7

#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
 
#pragma comment(lib,"ntdll.lib") // Need to link with ntdll.lib import library. You can find the ntdll.lib from the Windows DDK.
 
typedef struct _SYSTEM_PROCESS_INFO
{
    ULONG                   NextEntryOffset;
    ULONG                   NumberOfThreads;
    LARGE_INTEGER           Reserved[3];
    LARGE_INTEGER           CreateTime;
    LARGE_INTEGER           UserTime;
    LARGE_INTEGER           KernelTime;
    UNICODE_STRING          ImageName;
    ULONG                   BasePriority;
    HANDLE                  ProcessId;
    HANDLE                  InheritedFromProcessId;
}SYSTEM_PROCESS_INFO,*PSYSTEM_PROCESS_INFO;
 
int main()
{
    NTSTATUS status;
    PVOID buffer;
    PSYSTEM_PROCESS_INFO spi;
 
    buffer=VirtualAlloc(NULL,1024*1024,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE); // We need to allocate a large buffer because the process list can be large.
 
    if(!buffer)
    {
        printf("\nError: Unable to allocate memory for process list (%d)\n",GetLastError());
        return -1;
    }
 
    printf("\nProcess list allocated at address %#x\n",buffer);
    spi=(PSYSTEM_PROCESS_INFO)buffer;
 
    if(!NT_SUCCESS(status=NtQuerySystemInformation(SystemProcessInformation,spi,1024*1024,NULL)))
    {
        printf("\nError: Unable to query process list (%#x)\n",status);
 
        VirtualFree(buffer,0,MEM_RELEASE);
        return -1;
    }
 
    while(spi->NextEntryOffset) // Loop over the list until we reach the last entry.
    {
        printf("\nProcess name: %ws | Process ID: %d\n",spi->ImageName.Buffer,spi->ProcessId); // Display process information.
        spi=(PSYSTEM_PROCESS_INFO)((LPBYTE)spi+spi->NextEntryOffset); // Calculate the address of the next entry.
    }
     
    printf("\nPress any key to continue.\n");
    getchar();
 
    VirtualFree(buffer,0,MEM_RELEASE); // Free the allocated buffer.
    return 0;
}