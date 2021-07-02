#include <windows.h>
#include <stdio.h>
#include <tchar.h>

WORD flag = 0;

WORD buffer = 0;

DWORD WINAPI threadWriter(LPVOID);
DWORD WINAPI threadReader(LPVOID);

int _tmain()
{
	DWORD
		dwThread1Id,
		dwThread2Id;
	HANDLE
		hThread1 = CreateThread(NULL, 0, threadWriter, NULL, CREATE_SUSPENDED, &dwThread1Id),
		hThread2 = CreateThread(NULL, 0, threadReader, NULL, CREATE_SUSPENDED, &dwThread2Id);
	
	if (hThread1 == INVALID_HANDLE_VALUE || hThread1 == NULL) {
		_tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
		return GetLastError();
	}
	if (hThread2 == INVALID_HANDLE_VALUE || hThread2 == NULL) {
		CloseHandle(hThread1);
		_tprintf_s(_T("CreateThread failed (%u)\n"), GetLastError());
		return GetLastError();
	}
	ResumeThread(hThread1);
	ResumeThread(hThread2);
	WaitForMultipleObjects(2, new HANDLE[]{ hThread1, hThread2 }, TRUE, INFINITE);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
}

DWORD WINAPI threadWriter(LPVOID args) {
	for (int i = 0; i < 10; i++) {
		__asm {
		cycl:
			lock bts flag, 0
			jc cycl
		};
		buffer += 1;
		Sleep(500);
		__asm {
			lock btr flag, 0
		};
		
	}
	return 0;
}

DWORD WINAPI threadReader(LPVOID args) {
	for (int i = 0; i < 10; i++) {
		__asm {
		cycl:
			lock bts flag, 0
			jc cycl
		};
		_tprintf_s(_T("Buffer: %u\n"), buffer);
		__asm {
			lock btr flag, 0
		};
	}
	return 0;
}