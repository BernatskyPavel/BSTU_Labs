#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <errno.h>

void print_help();


int _tmain(int argc, TCHAR* argv[])
{
	TCHAR cmd1[256]; _tcscpy_s(cmd1, _T(".\\LAB_03_02x.exe"));
	TCHAR cmd2[256]; _tcscpy_s(cmd2, _T(".\\LAB_03_02x.exe"));

	STARTUPINFO si, si2;
	PROCESS_INFORMATION pi, pi2;

	ZeroMemory(&si, sizeof(si));    ZeroMemory(&si2, sizeof(si2));
	si.cb = sizeof(si);             si2.cb = sizeof(si2);
	ZeroMemory(&pi, sizeof(pi));    ZeroMemory(&pi2, sizeof(pi2));

	if (_tcscat_s(cmd1, L" 50") != 0) {
		printf("wcscat_s failed (%d)\n", GetLastError());
		return 1;
	}

	if (!CreateProcess(NULL, cmd1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		printf("CreateProcess failed (%d).\n", GetLastError());
		return 2;
	}

	if (wcscat_s(cmd2, L" 125") != 0) {
		TerminateProcess(pi.hProcess, 1);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		printf("wcscat_s 2 failed (%d).\n", GetLastError());
		return 3;
	}

	if (!CreateProcess(NULL, cmd2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | CREATE_SUSPENDED, NULL, NULL, &si2, &pi2)) {
		TerminateProcess(pi.hProcess, 1);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		printf("CreateProcess 2 failed (%d).\n", GetLastError());
		return 4;
	}
	
	ResumeThread(pi.hThread);
	ResumeThread(pi2.hThread);

	for (int i = 0; i < 100; i++) {
		_tprintf_s(_T("Process id: (%u)\n"), GetCurrentProcessId());
		Sleep(1000);
	}

	WaitForMultipleObjects(2, new HANDLE[]{ pi.hThread, pi2.hThread}, TRUE, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(pi2.hThread);
	CloseHandle(pi2.hProcess);

	return 0;
}