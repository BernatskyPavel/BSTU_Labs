#include <Windows.h>
#include <stdio.h>

int main()
{
    for (;;) {
        wprintf_s(L"Hello World!\n");
        Sleep(3000);
    }
}

/*
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

int main()
{
    LPVOID lpvAddr;               // address of the test memory
    DWORD dwPageSize;             // amount of memory to allocate.
    BOOL bLocked;                 // address of the guarded memory
    SYSTEM_INFO sSysInfo;         // useful information about the system

    GetSystemInfo(&sSysInfo);     // initialize the structure

    _tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);

    dwPageSize = sSysInfo.dwPageSize; // 44 pages max!

    // Try to allocate the memory.

    lpvAddr = VirtualAlloc(NULL, dwPageSize,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READONLY);

    if (lpvAddr == NULL) {
        _tprintf(TEXT("VirtualAlloc failed. Error: %ld\n"),
            GetLastError());
        return 1;

    }
    else {
        _ftprintf(stderr, TEXT("Committed %lu bytes at address 0x%lp\n"),
            dwPageSize, lpvAddr);
    }

    // Try to lock the committed memory. This fails the first time 
    // because of the guard page.

    bLocked = VirtualLock(lpvAddr, dwPageSize);
    if (!bLocked) {
        _ftprintf(stderr, TEXT("Cannot lock at %lp, error = 0x%lx\n"),
            lpvAddr, GetLastError());
    }
    else {
        _ftprintf(stderr, TEXT("Lock Achieved at %lp\n"), lpvAddr);
    }

    // Try to lock the committed memory again. This succeeds the second
    // time because the guard page status was removed by the first 
    // access attempt.

    bLocked = VirtualLock(lpvAddr, dwPageSize);

    if (!bLocked) {
        _ftprintf(stderr, TEXT("Cannot get 2nd lock at %lp, error = 0x%lx\n"),
            lpvAddr, GetLastError());
    }
    else {
        _ftprintf(stderr, TEXT("2nd Lock Achieved at %lp\n"), lpvAddr);
    }

    return 0;
}

*/
