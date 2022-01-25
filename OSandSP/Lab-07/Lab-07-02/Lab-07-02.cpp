#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#define THREAD_COUNTER 90

CRITICAL_SECTION section;
DWORD WINAPI threadProc(LPVOID);

int
_tmain()
{
  DWORD dwThread1Id;
  HANDLE hThread1 = CreateThread(NULL,
                                 0,
                                 threadProc,
                                 (LPVOID) _T("Thread A"),
                                 CREATE_SUSPENDED,
                                 &dwThread1Id);

  if (hThread1 == INVALID_HANDLE_VALUE || hThread1 == NULL) {
    _tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
    return GetLastError();
  }

  DWORD dwThread2Id;
  HANDLE hThread2 = CreateThread(NULL,
                                 0,
                                 threadProc,
                                 (LPVOID) _T("Thread B"),
                                 CREATE_SUSPENDED,
                                 &dwThread2Id);

  if (hThread2 == INVALID_HANDLE_VALUE || hThread2 == NULL) {
    CloseHandle(hThread1);
    _tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
    return GetLastError();
  }

  InitializeCriticalSection(&section);
  ResumeThread(hThread1);
  ResumeThread(hThread2);
  LPCTSTR name = _T("Thread Main");
  size_t i = 0;

  for (i; i < 90; i++) {
    if (i == 30) {
      EnterCriticalSection(&section);
    }
    if (i == 60) {
      LeaveCriticalSection(&section);
    }
    _tprintf_s(_T("%s: %zu\n"), name, i);
    Sleep(100);
  }

  WaitForMultipleObjects(2, new HANDLE[]{ hThread1, hThread2 }, TRUE, INFINITE);
  CloseHandle(hThread1);
  CloseHandle(hThread2);
  DeleteCriticalSection(&section);
}

DWORD WINAPI
threadProc(LPVOID args)
{
  LPCTSTR name = (LPCTSTR)args;
  size_t i = 0;

  for (i; i < 90; i++) {
    if (i == 30) {
      EnterCriticalSection(&section);
    }
    if (i == 60) {
      LeaveCriticalSection(&section);
    }
    _tprintf_s(_T("%s: %zu\n"), name, i);
    Sleep(100);
  }
  return 0;
}