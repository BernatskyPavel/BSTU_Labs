#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int
_tmain(int argc, TCHAR** argv)
{
  HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, _T("Lab-07-Event"));
  
  if (hEvent == INVALID_HANDLE_VALUE || hEvent == NULL) {
    _tprintf_s(L"CreateEvent failed! (%u)", GetLastError());
    return GetLastError();
  }

  STARTUPINFO si1;
  ZeroMemory(&si1, sizeof(si1));
  PROCESS_INFORMATION pi1;
  ZeroMemory(&pi1, sizeof(pi1));

  TCHAR cmd1[256];
  _tcscpy_s(cmd1, _T(".\\Lab-07-05a.exe"));

  if (_tcscat_s(cmd1, _T(" A")) != 0) {
    _tprintf_s(_T("_tcscat_s failed (%d)\n"), GetLastError());
    return 1;
  }
  if (!CreateProcess(NULL,
                     cmd1,
                     NULL,
                     NULL,
                     FALSE,
                     CREATE_NEW_CONSOLE | CREATE_SUSPENDED,
                     NULL,
                     NULL,
                     &si1,
                     &pi1)) {
    _tprintf_s(_T("CreateProcess failed (%d).\n"), GetLastError());
    return 2;
  }

  TCHAR cmd2[256];
  _tcscpy_s(cmd2, _T(".\\Lab-07-05a.exe"));

  if (_tcscat_s(cmd2, _T(" B")) != 0) {
    CloseHandle(pi1.hThread);
    CloseHandle(pi1.hProcess);
    _tprintf_s(_T("_tcscat_s failed (%d)\n"), GetLastError());
    return 3;
  }

  STARTUPINFO si2;
  ZeroMemory(&si2, sizeof(si2));
  PROCESS_INFORMATION pi2;
  ZeroMemory(&pi2, sizeof(pi2));

  if (!CreateProcess(NULL,
                     cmd2,
                     NULL,
                     NULL,
                     FALSE,
                     CREATE_NEW_CONSOLE | CREATE_SUSPENDED,
                     NULL,
                     NULL,
                     &si2,
                     &pi2)) {
    CloseHandle(pi1.hThread);
    CloseHandle(pi1.hProcess);
    _tprintf_s(_T("CreateProcess failed (%d).\n"), GetLastError());
    return 4;
  }

  ResumeThread(pi1.hThread);
  ResumeThread(pi2.hThread);

  size_t i = 0;
  for (i; i < 90; i++) {
    if (i == 15) {
      SetEvent(hEvent);
    }
    _tprintf_s(_T("Process(Main): %zu\n"), i);
    Sleep(100);
  }

  WaitForMultipleObjects(
    2, new HANDLE[]{ pi1.hThread, pi2.hThread }, TRUE, INFINITE);

  CloseHandle(hEvent);
  CloseHandle(pi1.hThread);
  CloseHandle(pi1.hProcess);
  CloseHandle(pi2.hThread);
  CloseHandle(pi2.hProcess);
  return 0;
}