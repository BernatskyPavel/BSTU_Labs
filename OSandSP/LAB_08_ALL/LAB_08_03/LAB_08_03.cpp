#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <tchar.h>

#define _SECOND 10000000
#define _PERIOD 3000

volatile unsigned counter;
clock_t start;
HANDLE hTimer;
void WINAPI TimerProc(LPVOID, DWORD, DWORD);
DWORD WINAPI ThreadProc(LPVOID);

int main()
{
	DWORD dThreadId = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, &dThreadId);
	
	if (hThread == INVALID_HANDLE_VALUE || hThread == NULL) {
		wprintf_s(L"CreateThread failed (%d)\n", GetLastError());
		return 3;
	}

	ResumeThread(hThread);
	start = clock();
	for (;;) {
		counter += 1;
		if ((double)(clock() - start) / CLOCKS_PER_SEC >= 15.0) {
			_tprintf_s(_T("Iteration counter after 15 seconds: %u\n"), counter);
			CancelWaitableTimer(hTimer);
			break;
		}
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}

void WINAPI TimerProc(
	LPVOID lpArgToCompletionRoutine,
	DWORD dwTimerLowValue,
	DWORD dwTimerHighValue
) {
	_tprintf_s(_T("Time: %f; Counter value: %u\n"), (double)(clock() - start) / CLOCKS_PER_SEC, counter);
	MessageBeep(0);
}

DWORD WINAPI ThreadProc(
	LPVOID arg
) {
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("3SecTimer"));
	if (hTimer == INVALID_HANDLE_VALUE || hTimer == NULL) {
		_tprintf_s(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}
	__int64         qwDueTime = 0 * _SECOND;
	LARGE_INTEGER   liDueTime;
	liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
	liDueTime.HighPart = (LONG)(qwDueTime >> 32);
	if (!SetWaitableTimer(hTimer, &liDueTime, _PERIOD, TimerProc, NULL, FALSE)) {
		_tprintf_s(_T("SetWaitableTimer failed (%d)\n"), GetLastError());
		return 2;
	}
	for (;;) {
		if (SleepEx(_PERIOD + 100, TRUE) == 0) {
			break;
		}
	}

	return 0;
}