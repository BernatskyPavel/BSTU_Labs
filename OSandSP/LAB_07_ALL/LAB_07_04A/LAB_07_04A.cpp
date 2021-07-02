#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int _tmain(int argc, TCHAR** argv)
{
	if (argc < 2) {
		_tprintf_s(_T("Name parameter not provided!"));
		return 1;
	}

	HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE, FALSE, L"LAB_07_Semaphore");
	if (hSemaphore == INVALID_HANDLE_VALUE || hSemaphore == NULL) {
		_tprintf_s(_T("OpenMutex failed! (%u)"), GetLastError());
		return GetLastError();
	}

	size_t i = 0;
	for (i; i < 30; i++)
	{
		_tprintf_s(_T("Process(%s): %I64u\n"), argv[1], i);
		Sleep(100);
	}
	WaitForSingleObject(hSemaphore, INFINITE);
	for (i; i < 60; i++) {
		_tprintf_s(_T("Process(%s): %I64u\n"), argv[1], i);
		Sleep(100);
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	CloseHandle(hSemaphore);
	for (i; i < 90; i++) {
		_tprintf_s(_T("Process(%s): %I64u\n"), argv[1], i);
		Sleep(100);
	}
}