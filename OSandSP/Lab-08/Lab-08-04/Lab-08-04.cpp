#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>

clock_t start;
HANDLE hTimer1, hTimer2;
void WINAPI TimerProc(LPVOID, DWORD, DWORD);
DWORD WINAPI ThreadProc(LPVOID);

struct ThreadData {
	LONG time;
	DWORD process_id;
};

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR cmd1[256]; _tcscpy_s(cmd1, _T(".\\Lab-08-04x.exe"));
	TCHAR cmd2[256]; _tcscpy_s(cmd2, _T(".\\Lab-08-04x.exe"));

	STARTUPINFO si, si2;
	PROCESS_INFORMATION pi, pi2;

	ZeroMemory(&si, sizeof(si));    ZeroMemory(&si2, sizeof(si2));
	si.cb = sizeof(si);             si2.cb = sizeof(si2);
	ZeroMemory(&pi, sizeof(pi));    ZeroMemory(&pi2, sizeof(pi2));

	if (_tcscat_s(cmd1, _T(" 60")) != 0) {
		_tprintf(_T("_tcscat_s failed (%d)\n"), GetLastError());
		return 1;
	}

	if (!CreateProcess(NULL, cmd1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		_tprintf(_T("CreateProcess failed (%d).\n"), GetLastError());
		return 2;
	}

	if (wcscat_s(cmd2, L" 120") != 0) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		_tprintf(_T("_tcscat_s failed (%d)\n"), GetLastError());
		return 3;
	}

	if (!CreateProcess(NULL, cmd2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		_tprintf(_T("CreateProcess failed (%d).\n"), GetLastError());
		return 4;
	}

	WaitForMultipleObjects(2, new HANDLE[]{ pi.hProcess, pi2.hProcess }, TRUE, INFINITE);
	
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(pi2.hThread);
	CloseHandle(pi2.hProcess);

	return 0;
}