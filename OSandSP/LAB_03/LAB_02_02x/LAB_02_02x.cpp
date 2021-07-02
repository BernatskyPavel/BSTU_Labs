#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <processthreadsapi.h>

#define CYCLE_SIZE 1000000

int _tmain(void)
{
    

    for (int i = 0; i < CYCLE_SIZE; i++) {
        if ((i + 1) % 1000 == 0) {

            _tprintf_s(_T("Iteration number: %u\n"), (i + 1));
            _tprintf_s(_T("Process id: %u\n"), GetCurrentProcessId());
            _tprintf_s(_T("Main thread id: %u\n"), GetCurrentThreadId());
            _tprintf_s(_T("Process priority class: %s\n"), priority_class);
            _tprintf_s(_T("Main thread priority: %s\n"), priority_thread);
            _tprintf_s(_T("%s\n"), ideal_process);

            Sleep(1000);
        }
    }
    _tsystem(_T("pause"));
}