#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define PAGELIMIT 256

LPINT lpNxtPage;               // Address of the next page to ask for
DWORD dwPages = 0;              // Count of pages gotten so far
DWORD dwPageSize;               // Page size on this computer

INT PageFaultExceptionFilter(DWORD dwCode)
{
	LPVOID lpvResult;
	// If the exception is not a page fault, exit.

	if (dwCode != EXCEPTION_ACCESS_VIOLATION)
	{
		_tprintf(TEXT("Exception code = %d.\n"), dwCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	_tprintf(TEXT("Exception is a page fault.\n"));

	// If the reserved pages are used up, exit.

	if (dwPages >= PAGELIMIT)
	{
		_tprintf(TEXT("Exception: out of pages.\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Otherwise, commit another page.

	lpvResult = VirtualAlloc(
		(LPVOID)lpNxtPage,  // Next page to commit
		dwPageSize,         // Page size, in bytes
		MEM_COMMIT,         // Allocate a committed page
		PAGE_READWRITE);    // Read/write access
	if (lpvResult == NULL)
	{
		_tprintf(TEXT("VirtualAlloc failed.\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		_tprintf(TEXT("Allocating another page.\n"));
	}

	// Increment the page count, and advance lpNxtPage to the next page.

	dwPages++;
	lpNxtPage = (LPINT)(lpNxtPage + dwPageSize);

	// Continue execution where the page fault occurred.

	return EXCEPTION_CONTINUE_EXECUTION;
}

int _tmain(void)
{
	LPVOID lpvBase;               // Base address of the test memory
	LPINT lpPtr;                 // Generic character pointer
	BOOL bSuccess;                // Flag
	INT i;                      // Generic counter
	SYSTEM_INFO sSysInfo;         // Useful information about the system

	GetSystemInfo(&sSysInfo);     // initialize the structure

	_tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);

	dwPageSize = sSysInfo.dwPageSize;

	lpvBase = VirtualAlloc(NULL, PAGELIMIT * static_cast<SIZE_T>(dwPageSize), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (lpvBase == NULL) {
		_tprintf(TEXT("Error! VirtualAlloc reserve failed with error code of %ld.\n"),
			GetLastError());
		return 0;
	}

	lpPtr = lpNxtPage = (LPINT)lpvBase;

	for (i = 0; i < (PAGELIMIT * static_cast<unsigned long long>(dwPageSize)) / sizeof(int); i++)
	{
		__try
		{
			// Write to memory.
			lpPtr[i] = i;
			printf("i=%d\n", i);
		}
		// If there's a page fault, commit another page and try again.
		__except (PageFaultExceptionFilter(GetExceptionCode()))
		{
			// This code is executed only if the filter function
			// is unsuccessful in committing the next page.
			_tprintf(TEXT("Exiting process.\n"));
			ExitProcess(GetLastError());

		}

	}
	system("pause");
	// Release the block of pages when you are finished using them.
	bSuccess = VirtualFree(
		lpvBase,       // Base address of block
		0,             // Bytes of committed pages
		MEM_RELEASE);  // Decommit the pages

	_tprintf(TEXT("Release %s.\n"), bSuccess ? TEXT("succeeded") : TEXT("failed"));

	return 0;
}