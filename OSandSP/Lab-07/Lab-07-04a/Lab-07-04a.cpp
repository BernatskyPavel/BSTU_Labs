#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int
_tmain(int argc, TCHAR** argv)
{
  if (argc < 2) {
    _tprintf_s(_T("Name parameter not provided!"));
    return 1;
  }

  HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE, FALSE, _T("Lab-07-Semaphore"));
  if (hSemaphore == INVALID_HANDLE_VALUE || hSemaphore == NULL) {
    _tprintf_s(_T("OpenMutex failed! (%u)"), GetLastError());
    return GetLastError();
  }

  size_t i = 0;
  for (i; i < 90; i++) {
    if (i == 30) {
      WaitForSingleObject(hSemaphore, INFINITE);
    }
    if (i == 60) {
      ReleaseSemaphore(hSemaphore, 1, NULL);
      CloseHandle(hSemaphore);
    }
    _tprintf_s(_T("Process(%s): %zu\n"), argv[1], i);
    Sleep(100);
  }
}