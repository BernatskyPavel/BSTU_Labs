#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int
_tmain(void)
{
  for (;;) {
    _tprintf_s(L"Hello World!\n");
    Sleep(3000);
  }
}