#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define PAGELIMIT 256

LPINT lpNxtPage;
DWORD dwPages = 0;
DWORD dwPageSize;

INT
PageFaultExceptionFilter(DWORD dwCode)
{
  LPVOID lpvResult;

  if (dwCode != EXCEPTION_ACCESS_VIOLATION) {
    _tprintf(TEXT("Exception code = %d.\n"), dwCode);
    return EXCEPTION_EXECUTE_HANDLER;
  }

  _tprintf(TEXT("Exception is a page fault.\n"));

  if (dwPages >= PAGELIMIT) {
    _tprintf(TEXT("Exception: out of pages.\n"));
    return EXCEPTION_EXECUTE_HANDLER;
  }

  lpvResult =
    VirtualAlloc((LPVOID)lpNxtPage, dwPageSize, MEM_COMMIT, PAGE_READWRITE);

  if (lpvResult == NULL) {
    _tprintf(TEXT("VirtualAlloc failed.\n"));
    return EXCEPTION_EXECUTE_HANDLER;
  } else {
    _tprintf(TEXT("Allocating another page.\n"));
  }
  dwPages++;
  lpNxtPage = (LPINT)(lpNxtPage + dwPageSize);

  return EXCEPTION_CONTINUE_EXECUTION;
}

int
_tmain(void)
{
  LPVOID lpvBase;
  LPINT lpPtr;
  BOOL bSuccess;
  INT i;
  SYSTEM_INFO sSysInfo;

  GetSystemInfo(&sSysInfo);
  _tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);
  dwPageSize = sSysInfo.dwPageSize;

  lpvBase = VirtualAlloc(NULL,
                         PAGELIMIT * static_cast<INT>(dwPageSize),
                         MEM_COMMIT | MEM_RESERVE,
                         PAGE_READWRITE);

  if (lpvBase == NULL) {
    _tprintf(
      TEXT("Error! VirtualAlloc reserve failed with error code of %ld.\n"),
      GetLastError());
    return 0;
  }

  lpPtr = lpNxtPage = (LPINT)lpvBase;

  for (i = 0; i < (PAGELIMIT * static_cast<INT>(dwPageSize)) / sizeof(INT);
       i++) {
    __try {
      *(lpPtr + i) = i;
    } __except (PageFaultExceptionFilter(GetExceptionCode())) {
      _tprintf(TEXT("Exiting process.\n"));
      ExitProcess(GetLastError());
    }
  }
  system("pause");

  bSuccess = VirtualFree(lpvBase, 0, MEM_RELEASE);

  _tprintf(TEXT("Release %s.\n"),
           bSuccess ? TEXT("succeeded") : TEXT("failed"));

  return 0;
}