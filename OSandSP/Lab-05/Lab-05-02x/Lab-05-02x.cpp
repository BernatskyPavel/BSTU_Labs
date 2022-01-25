#include <Windows.h>
#include <processthreadsapi.h>
#include <stdio.h>
#include <tchar.h>

#define CYCLE_SIZE 1000000

int
_tmain(void)
{
  HANDLE current_process = GetCurrentProcess();
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

  PROCESSOR_NUMBER thread_processor;
  TCHAR ideal_process[256];

  if (TRUE != GetThreadIdealProcessorEx(current_thread, &thread_processor)) {
    _stprintf_s(ideal_process,
                _T("GetThreadIdealProcessorEx failed (%u)"),
                GetLastError());
  } else {
    _stprintf_s(
      ideal_process, _T("Ideal process CPU: %d\n"), thread_processor.Number);
  }

  for (int i = 0; i < CYCLE_SIZE; i++) {
    if ((i + 1) % 1000 == 0) {
      _tprintf_s(_T("Iteration number: %u\n"), (i + 1));
      _tprintf_s(_T("Process id: %u\n"), GetCurrentProcessId());
      _tprintf_s(_T("Main thread id: %u\n"), GetCurrentThreadId());
      _tprintf_s(_T("Process priority class: %s\n"), priority_class);
      _tprintf_s(_T("Main thread priority: %s\n"), priority_thread);
      _tprintf_s(_T("%s\n"), ideal_process);
      Sleep(200);
    }
  }
  _tsystem(_T("pause"));
}