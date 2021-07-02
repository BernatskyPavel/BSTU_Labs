#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int _tmain(int argc, TCHAR** argv)
{
	SECURITY_ATTRIBUTES security;
	security.bInheritHandle = TRUE;
	security.lpSecurityDescriptor = NULL;
	security.nLength = sizeof(security);
	HANDLE hMutex = CreateMutex(&security, FALSE, _T("a"));
	if (hMutex == INVALID_HANDLE_VALUE || hMutex == NULL) {
		_tprintf_s(_T("CreateMutex failed! (%u)"), GetLastError());
		return GetLastError();
	}

	STARTUPINFO si1, si2;
	ZeroMemory(&si1, sizeof(si1));
	ZeroMemory(&si2, sizeof(si2));
	PROCESS_INFORMATION pi1, pi2;
	ZeroMemory(&pi1, sizeof(pi1));
	ZeroMemory(&pi2, sizeof(pi2));
	
	TCHAR cmd1[256]; _tcscpy_s(cmd1, _T(".\\Lab-07-03a.exe"));
	TCHAR cmd2[256]; _tcscpy_s(cmd2, _T(".\\Lab-07-03a.exe"));
	
	if (_tcscat_s(cmd1, _T(" A")) != 0) {
		_tprintf_s(_T("_tcscat_s failed (%d)\n"), GetLastError());
		return 1;
	}
	if (!CreateProcess(NULL, cmd1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | CREATE_SUSPENDED, NULL, NULL, &si1, &pi1)) {
		_tprintf_s(_T("CreateProcess failed (%d)\n"), GetLastError());
		return 2;
	}

	if (_tcscat_s(cmd2, _T(" B")) != 0) {
		CloseHandle(pi1.hThread);
		CloseHandle(pi1.hProcess);
		_tprintf_s(_T("_tcscat_s failed (%d)\n"), GetLastError());
		return 3;
	}
	if (!CreateProcess(NULL, cmd2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | CREATE_SUSPENDED, NULL, NULL, &si2, &pi2)) {
		CloseHandle(pi1.hThread);
		CloseHandle(pi1.hProcess);
		_tprintf_s(_T("CreateProcess failed (%d)\n"), GetLastError());
		return 4;
	}

	ResumeThread(pi1.hThread);
	ResumeThread(pi2.hThread);

	size_t i = 0;
	for (i; i < 30; i++)
	{
		_tprintf_s(_T("Process(Main): %zu\n"), i);
		Sleep(100);
	}
	WaitForSingleObject(hMutex, INFINITE);
	for (i; i < 60; i++) {
		_tprintf_s(_T("Process(Main): %zu\n"), i);
		Sleep(100);
	}
	ReleaseMutex(hMutex);
	for (i; i < 90; i++) {
		_tprintf_s(_T("Process(Main): %zu\n"), i);
		Sleep(100);
	}	
	WaitForMultipleObjects(2, new HANDLE[]{ pi1.hThread , pi2.hThread }, TRUE, INFINITE);
	CloseHandle(hMutex);
	CloseHandle(pi1.hThread);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hThread);
	CloseHandle(pi2.hProcess);
	return 0;
}