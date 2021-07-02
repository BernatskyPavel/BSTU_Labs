#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <errno.h>

#define CYCLE_SIZE 1000000

void print_help();
DWORD WINAPI threadProc(LPVOID);

int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 4) {
		_tprintf_s(_T("Missing arguments!\n"));
		print_help();
		return -1;
	}

	for (int i = 1; i < 5; i++) {
		_tprintf_s(_T("Argument %u is %s\n"), i, argv[i]);
	}

	DWORD affinity_mask = _ttoi(argv[1]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid affinity mask value!\n"));
		return 1;
	}

	int process_priority = _ttoi(argv[2]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid priority value!\n"));
		return 7;
	}

	int thread_one_priority = _ttoi(argv[3]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid priority value!\n"));
		return 2;
	}

	int thread_two_priority = _ttoi(argv[4]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid priority value!\n"));
		return 3;
	}

	if (TRUE != SetProcessAffinityMask(GetCurrentProcess(), affinity_mask)) {
		_tprintf_s(_T("SetProcessAffinityMask failed (%u)!\n"), GetLastError());
		return 4;
	}

	if (TRUE != SetPriorityClass(GetCurrentProcess(), process_priority)) {
		_tprintf_s(_T("SetPriorityClass failed (%u)!\n"), GetLastError());
		return 8;
	}

    HANDLE hThread1, hThread2;
    DWORD dwThread1Id, dwThread2Id;
	
    hThread1 = CreateThread(NULL, 0, threadProc, NULL, CREATE_SUSPENDED, &dwThread1Id);
    
    if (hThread1 == INVALID_HANDLE_VALUE || hThread1 == NULL){
        _tprintf_s(_T("CreateThread failed (%u)!\n"), GetLastError());
        return 5;
    }

    hThread2 = CreateThread(NULL, 0, threadProc, NULL, CREATE_SUSPENDED, &dwThread2Id);
    
    if (hThread2 == INVALID_HANDLE_VALUE || hThread2 == NULL) {
        CloseHandle(hThread1);
        _tprintf_s(_T("CreateThread failed (%u)!\n"), GetLastError());
        return 5;
    }
	
    if (!SetThreadPriority(hThread1, thread_one_priority)) {
        CloseHandle(hThread1);
        CloseHandle(hThread2);
        _tprintf_s(_T("SetThreadPriority failed (%u)!\n"), GetLastError());
        return 9;
    }

    if (!SetThreadPriority(hThread2, thread_two_priority)) {
        CloseHandle(hThread1);
        CloseHandle(hThread2);
        _tprintf_s(_T("SetThreadPriority failed (%u)!\n"), GetLastError());
        return 10;
    }

	ResumeThread(hThread1);
	ResumeThread(hThread2);
	WaitForMultipleObjects(2, new HANDLE[]{ hThread1, hThread2 }, TRUE, INFINITE);
    CloseHandle(hThread1);
    CloseHandle(hThread2);

	return EXIT_SUCCESS;
}

void print_help() {
	_tprintf_s(_T("Usage: Lab-05-03.exe <Affinity> <Process priority> <Thread 1 priority> <Thread 2 priority>\n"));
	_tprintf_s(_T("Affinity: Number which binary representation show which cores of CPU can be used by process.\n"));
	_tprintf_s(_T("Process Info:\n"));
	_tprintf_s(_T("Priority: Realtime - %u\n"), REALTIME_PRIORITY_CLASS);
	_tprintf_s(_T("	  High - %u\n"), HIGH_PRIORITY_CLASS);
	_tprintf_s(_T("	  Above normal - %u\n"), ABOVE_NORMAL_PRIORITY_CLASS);
	_tprintf_s(_T("	  Normal - %u\n"), NORMAL_PRIORITY_CLASS);
	_tprintf_s(_T("	  Below normal - %u\n"), BELOW_NORMAL_PRIORITY_CLASS);
	_tprintf_s(_T("	  Idle - %u\n"), IDLE_PRIORITY_CLASS);
	_tprintf_s(_T("Thread Info:\n"));
    _tprintf_s(_T("Priority: Time critical - %d\n"), THREAD_PRIORITY_TIME_CRITICAL);
	_tprintf_s(_T("	  Highest - %d\n"), THREAD_PRIORITY_HIGHEST);
	_tprintf_s(_T("	  Above normal - %d\n"), THREAD_PRIORITY_ABOVE_NORMAL);
	_tprintf_s(_T("	  Normal - %d\n"), THREAD_PRIORITY_NORMAL);
	_tprintf_s(_T("	  Below normal - %d\n"), THREAD_PRIORITY_BELOW_NORMAL);
	_tprintf_s(_T("	  Lowest - %d\n"), THREAD_PRIORITY_LOWEST);
	_tprintf_s(_T("	  Idle - %d\n"), THREAD_PRIORITY_IDLE);
}

DWORD WINAPI threadProc(LPVOID args) {
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
        _stprintf_s(ideal_process, _T("GetThreadIdealProcessorEx failed (%u)"), GetLastError());
    }
    else {
        _stprintf_s(ideal_process, _T("Ideal process CPU: %d\n"), thread_processor.Number);
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
    return 0;
}
