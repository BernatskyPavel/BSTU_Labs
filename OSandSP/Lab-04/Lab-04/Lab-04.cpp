#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int _tmain()
{
    for (;;) {
        _tprintf_s(_T("Process id: (%u); Thread id: (%u)\n"), GetCurrentProcessId(), GetCurrentThreadId());
        Sleep(1000);
    }
}