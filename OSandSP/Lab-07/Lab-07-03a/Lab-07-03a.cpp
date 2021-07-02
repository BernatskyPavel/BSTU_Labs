#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int _tmain(int argc, TCHAR** argv)
{
	if (argc < 2) {
		_tprintf_s(_T("Name parameter not provided!"));
		return 1;
	}
	HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, _T("Lab-07-Mutex"));
	if (hMutex == INVALID_HANDLE_VALUE || hMutex == NULL) {
		_tprintf_s(_T("OpenMutex failed! (%u)"), GetLastError());
		return GetLastError();
	}
	size_t i = 0;
	for (i; i < 30; i++)
	{
		_tprintf_s(_T("Process(%s): %zu\n"), argv[1], i);
		Sleep(100);
	}
	WaitForSingleObject(hMutex, INFINITE);
	for (i; i < 60; i++) {
		_tprintf_s(_T("Process(%s): %zu\n"), argv[1], i);
		Sleep(100);
	}
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	for (i; i < 90; i++) {
		_tprintf_s(_T("Process(%s): %zu\n"), argv[1], i);
		Sleep(100);
	}
}