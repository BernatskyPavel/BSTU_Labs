#include <stdio.h>
#include <tchar.h>
#include <windows.h>

WORD flag = 0;
WORD buffer = 0;

DWORD WINAPI threadWriter(LPVOID);
DWORD WINAPI threadReader(LPVOID);

int
_tmain()
{
  DWORD dwThread1Id;
  HANDLE hThread1 =
    CreateThread(NULL, 0, threadWriter, NULL, CREATE_SUSPENDED, &dwThread1Id);

  if (hThread1 == INVALID_HANDLE_VALUE || hThread1 == NULL) {
    _tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
    return GetLastError();
  }

  DWORD dwThread2Id;
  HANDLE hThread2 =
    CreateThread(NULL, 0, threadReader, NULL, CREATE_SUSPENDED, &dwThread2Id);

  if (hThread2 == INVALID_HANDLE_VALUE || hThread2 == NULL) {
    CloseHandle(hThread1);
    _tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
    return GetLastError();
  }
  ResumeThread(hThread1);
  ResumeThread(hThread2);
  WaitForMultipleObjects(2, new HANDLE[]{ hThread1, hThread2 }, TRUE, INFINITE);
  CloseHandle(hThread1);
  CloseHandle(hThread2);
}

DWORD WINAPI
threadWriter(LPVOID args)
{
  for (int i = 0; i < 10; i++) {
    __asm {
        cycl:
            bt flag, 0
            jc cycl
			lock bts flag, 0
    }
    buffer += 1;
    __asm {
			lock btr flag, 1
    }
  }
  return 0;
}

DWORD WINAPI
threadReader(LPVOID args)
{
  for (int i = 0; i < 10; i++) {
    __asm {
		cycl:
			bt flag, 1
            jc cycl
			lock bts flag, 1
    }
    _tprintf_s(_T("Buffer: %u\n"), buffer);
    __asm {
			lock btr flag, 0
    }
  }
  return 0;
}