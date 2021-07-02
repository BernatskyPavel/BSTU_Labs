#include <Windows.h>
#include <stdio.h>
#include <cmath>
#include <tchar.h>

#define _SECOND 10000000

bool is_prime(unsigned int);
void WINAPI TimerProc(LPVOID, DWORD, DWORD);
DWORD WINAPI ThreadProc(LPVOID);
bool isSignaled = false;

int _tmain(int argc, TCHAR** argv)
{
	if (argc != 2) {
		_tprintf_s(_T("Startup failed. Usage: Lab-08-04x.exe <TIME>. Time must be in seconds.\n"));
		return 1;
	}

	LONG time = _wtol(argv[1]);
	DWORD dThreadId = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, &time, CREATE_SUSPENDED, &dThreadId);
	
	if (hThread == INVALID_HANDLE_VALUE || hThread == NULL) {
		wprintf_s(L"CreateThread failed (%d)\n", GetLastError());
		return 3;
	}

	ResumeThread(hThread);
	unsigned int counter = 0, i = 0;
	while (!isSignaled) {
		if (is_prime(i)) {
			_tprintf_s(_T("\nProcess %u - prime number %u: %u"), GetCurrentProcessId(), counter, i);
			counter += 1;
		}
		i += 1;
	}

	return 0;
}

bool is_prime(unsigned int n)
{
	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	for (unsigned int i = 2; i <= sqrt(n); ++i)
		if (n % i == 0)
			return false;
	return true;
}


DWORD WINAPI ThreadProc(
	LPVOID arg
) {
	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	
	if (hTimer == INVALID_HANDLE_VALUE || hTimer == NULL) {
		_tprintf_s(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	__int64         qwDueTime = -static_cast<__int64>(*reinterpret_cast<LPLONG>(arg)) * _SECOND;
	LARGE_INTEGER   liDueTime;
	liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
	liDueTime.HighPart = (LONG)(qwDueTime >> 32);
	if (!SetWaitableTimer(hTimer, &liDueTime, 0, TimerProc, NULL, FALSE)) {
		_tprintf_s(_T("SetWaitableTimer failed (%d)\n"), GetLastError());
		return 2;
	}
	SleepEx(INFINITE, TRUE);

	return 0;
}

void WINAPI TimerProc(
	LPVOID lpArgToCompletionRoutine,
	DWORD dwTimerLowValue,
	DWORD dwTimerHighValue
) {
	isSignaled = true;
}
