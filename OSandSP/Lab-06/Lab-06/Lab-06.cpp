#include <Windows.h>
#include <stdio.h>

int
main()
{
  for (;;) {
    wprintf_s(L"Hello World!\n");
    Sleep(3000);
  }
}
