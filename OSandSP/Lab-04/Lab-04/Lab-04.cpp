#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int
_tmain()
{
  unsigned long long i = 0;
  for (i; i < MAXULONGLONG; i++) {
    if (!(i % 1000000))
      _tprintf_s(_T("Process id: (%u); Thread id: (%u)\n"),
                 GetCurrentProcessId(),
                 GetCurrentThreadId());
  }
}