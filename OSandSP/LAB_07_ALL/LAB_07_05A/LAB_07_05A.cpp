#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int _tmain(int argc, TCHAR** argv)
{
	if (argc < 2) {
		_tprintf_s(_T("Name parameter not provided!"));
		return 1;
	}

	HANDLE hEvent = OpenEvent(SYNCHRONIZE, FALSE, _T("LAB_07_Event"));
	if (hEvent == INVALID_HANDLE_VALUE || hEvent == NULL) {
		_tprintf_s(_T("OpenEvent failed! (%u)"), GetLastError());
		return GetLastError();
	}
	
	size_t i = 0;
	WaitForSingleObject(hEvent, INFINITE);
	for (i; i < 90; i++)
	{
		_tprintf_s(_T("Process(%ws): %I64u\n"), argv[1], i);
		Sleep(100);
	}
	
	CloseHandle(hEvent);
	return 0;
}