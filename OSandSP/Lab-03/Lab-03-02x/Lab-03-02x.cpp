#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int
_tmain(int argc, TCHAR* argv[])
{
  if (argc < 2) {
    _tprintf_s(_T("Missing arguments!\n"));
    return 1;
  }

  INT cycle_size = _ttoi(argv[1]);

  if (errno == EINVAL) {
    _tprintf_s(_T("Invalid argument value (must be int)!\n"));
    return 2;
  }

  for (int i = 0; i < cycle_size; i++) {
    _tprintf_s(_T("Process id: (%u)\n"), GetCurrentProcessId());
    Sleep(1000);
  }
  _tsystem(_T("pause"));
  return 0;
}