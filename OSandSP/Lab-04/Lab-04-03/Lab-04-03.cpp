#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

DWORD WINAPI threadProc(LPVOID);

struct THREAD_DATA
{
  LPCTSTR name;
  DWORD max_iter;
};

int
_tmain()
{
  HANDLE hThread1, hThread2;
  DWORD dwThread1Id, dwThread2Id;
  THREAD_DATA
  thread1_data{ _T("T1"), 50 }, thread2_data{ _T("T2"), 125 };

  hThread1 = CreateThread(
    NULL, 0, threadProc, (LPVOID)&thread1_data, CREATE_SUSPENDED, &dwThread1Id);
  if (hThread1 == INVALID_HANDLE_VALUE || hThread1 == NULL) {
    _tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
    return 1;
  }

  hThread2 = CreateThread(
    NULL, 0, threadProc, (LPVOID)&thread2_data, CREATE_SUSPENDED, &dwThread2Id);
  if (hThread2 == INVALID_HANDLE_VALUE || hThread2 == NULL) {
    CloseHandle(hThread1);
    _tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
    return 2;
  }

  ResumeThread(hThread1);
  ResumeThread(hThread2);

  for (int i = 0; i < 100; i++) {
    switch (i) {
      case 19:
        _tprintf_s(_T("Thread T1 is going to be suspended.\n"));
        SuspendThread(hThread1);
        break;
      case 39:
        _tprintf_s(_T("Thread T2 is going to be suspended.\n"));
        SuspendThread(hThread2);
        break;
      case 59:
        _tprintf_s(_T("Thread T1 is going to be resumed.\n"));
        ResumeThread(hThread1);
        break;
      default:
        break;
    }
    _tprintf_s(_T("Thread Main (%u) - process id (%u), thread id (%u)\n"),
               i + 1,
               GetCurrentProcessId(),
               GetCurrentThreadId());
    Sleep(1000);
  }
  _tprintf_s(_T("Thread T1 is going to be resumed.\n"));
  ResumeThread(hThread2);

  WaitForMultipleObjects(2, new HANDLE[]{ hThread1, hThread2 }, TRUE, INFINITE);

  CloseHandle(hThread1);
  CloseHandle(hThread2);

  return 0;
}

DWORD WINAPI
threadProc(LPVOID args)
{
  THREAD_DATA* data = (THREAD_DATA*)args;

  for (DWORD i = 0; i < data->max_iter; i++) {
    _tprintf_s(_T("Thread %s (%u) - process id (%u), thread id (%u)\n"),
               data->name,
               i + 1,
               GetCurrentProcessId(),
               GetCurrentThreadId());
    Sleep(1000);
  }
  return 0;
}