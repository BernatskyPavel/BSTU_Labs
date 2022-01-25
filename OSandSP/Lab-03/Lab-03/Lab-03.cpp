#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int
_tmain()
{
  for (;;) {
    _tprintf_s(_T("Process id: (%u)\n"), GetCurrentProcessId());
    Sleep(1000);
  }
}