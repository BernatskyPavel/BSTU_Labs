#include <Windows.h>
#include <stdio.h>
#include <processthreadsapi.h>
#include <tchar.h>

int _tmain(void)
{
    HANDLE current_process = GetCurrentProcess();
    _tprintf_s(_T("Process id: %u\n"), GetCurrentProcessId());
    _tprintf_s(_T("Main thread id: %u\n"), GetCurrentThreadId());

    LPCTSTR priority_class;
    
    switch (GetPriorityClass(current_process)) {
    case ABOVE_NORMAL_PRIORITY_CLASS:
        priority_class = _T("ABOVE_NORMAL_PRIORITY_CLASS");
        break;
    case BELOW_NORMAL_PRIORITY_CLASS:
        priority_class = _T("BELOW_NORMAL_PRIORITY_CLASS");
        break;
    case HIGH_PRIORITY_CLASS:
        priority_class = _T("HIGH_PRIORITY_CLASS");
        break;
    case IDLE_PRIORITY_CLASS:
        priority_class = _T("IDLE_PRIORITY_CLASS");
        break;
    case NORMAL_PRIORITY_CLASS:
        priority_class = _T("NORMAL_PRIORITY_CLASS");
        break;
	case REALTIME_PRIORITY_CLASS:
        priority_class = _T("REALTIME_PRIORITY_CLASS");
        break;
    default:
        priority_class = _T("UNSUPPORTED_PRIORITY_CLASS");
        break;
    }
    _tprintf_s(_T("Process priority class: %s\n"), priority_class);
    
    HANDLE current_thread = GetCurrentThread();
    LPCTSTR priority_thread;
    
    switch (GetPriorityClass(current_thread)) {
    case THREAD_PRIORITY_IDLE:
        priority_thread = _T("THREAD_PRIORITY_IDLE");
        break;
    case THREAD_PRIORITY_LOWEST:
        priority_thread = _T("THREAD_PRIORITY_LOWEST");
        break;
    case THREAD_PRIORITY_BELOW_NORMAL:
        priority_thread = _T("THREAD_PRIORITY_BELOW_NORMAL");
        break;
    case THREAD_PRIORITY_NORMAL:
        priority_thread = _T("THREAD_PRIORITY_NORMAL");
        break;
    case THREAD_PRIORITY_ABOVE_NORMAL:
        priority_thread = _T("THREAD_PRIORITY_ABOVE_NORMAL");
        break;
    case THREAD_PRIORITY_HIGHEST:
        priority_thread = _T("THREAD_PRIORITY_HIGHEST");
        break;
    case THREAD_PRIORITY_TIME_CRITICAL:
        priority_thread = _T("THREAD_PRIORITY_TIME_CRITICAL");
        break;
    default:
        priority_thread = _T("UNSUPPORTED_THREAD_PRIORITY");
        break;
    }
    _tprintf_s(_T("Main thread priority: %s\n"), priority_thread);
    
    ULONG_PTR  
        process_affinity_mask,
        system_affinity_mask;
    
    if (TRUE != GetProcessAffinityMask(current_process, &process_affinity_mask, &system_affinity_mask)) {
        _tprintf_s(_T("GetProcessAffinityMask failed (%u)\n"), GetLastError());
    }
    else {
        TCHAR buffer_pr[65];
        _ultot_s((ULONG)process_affinity_mask, buffer_pr, 2);
        _tprintf_s(_T("Process CPU affinity: %s\n"), buffer_pr);

        byte bits = 0;
        while (process_affinity_mask) {
            if (process_affinity_mask & 1) {
                bits += 1;
            }
            process_affinity_mask >>= 1;
        }
        _tprintf_s(_T("Process CPU available: %d\n"), bits);
    }
    
    PROCESSOR_NUMBER thread_processor;
   
    if (TRUE != GetThreadIdealProcessorEx(current_thread, &thread_processor)) {
        _tprintf_s(_T("GetThreadIdealProcessorEx failed (%u)\n"), GetLastError());
    }
    else {
        _tprintf_s(_T("Ideal process CPU: %d\n"), thread_processor.Number);
    }
    
    return EXIT_SUCCESS;
}