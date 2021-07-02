#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <errno.h>

void print_help();


int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 4) {
		_tprintf_s(_T("Missing arguments!\n"));
		print_help();
		return -1;
	}

	for (int i = 1; i < 4; i++) {
		_tprintf_s(_T("Argument %u is %s\n"), i, argv[i]);
	}

	DWORD affinity_mask = _ttoi(argv[1]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid affinity mask value!\n"));
		return 1;
	}

	int process_one_priority = _ttoi(argv[2]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid priority value!\n"));
		return 2;
	}

	int process_two_priority = _ttoi(argv[3]);

	if (errno == EINVAL) {
		_tprintf_s(_T("Invalid priority value!\n"));
		return 3;
	}

	if (TRUE != SetProcessAffinityMask(GetCurrentProcess(), affinity_mask)) {
		_tprintf_s(_T("SetProcessAffinityMask failed (%u)!\n"), GetLastError());
		return 4;
	}

	STARTUPINFO
		process_one_startup,
		process_two_startup;
	ZeroMemory(&process_one_startup, sizeof(process_one_startup));
	ZeroMemory(&process_two_startup, sizeof(process_two_startup));
	process_one_startup.cb = sizeof(STARTUPINFO);
	process_two_startup.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION
		process_one_info,
		process_two_info;
	ZeroMemory(&process_one_info, sizeof(process_one_info));
	ZeroMemory(&process_two_info, sizeof(process_two_info));
	WCHAR path[] = L".\\Lab-05-02x.exe";
	
	if (!CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE | process_one_priority, NULL, NULL, &process_one_startup, &process_one_info)) {
		_tprintf_s(_T("CreateProcess failed (%u)!\n"), GetLastError());
		return 5;
	}
	if (!CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE | process_two_priority, NULL, NULL, &process_two_startup, &process_two_info)) {
		CloseHandle(process_one_info.hThread);
		CloseHandle(process_one_info.hProcess);
		_tprintf_s(_T("CreateProcess failed (%u)!\n"), GetLastError());
		return 6;
	}

	ResumeThread(process_one_info.hThread);
	ResumeThread(process_two_info.hThread);
	WaitForMultipleObjects(2, new HANDLE[]{ process_one_info.hThread , process_two_info.hThread }, TRUE, INFINITE);
	CloseHandle(process_one_info.hThread);
	CloseHandle(process_two_info.hThread);
	CloseHandle(process_two_info.hProcess);
	CloseHandle(process_one_info.hProcess);

	return EXIT_SUCCESS;
}

void print_help() {
	_tprintf_s(_T("Usage: Lab-05-02.exe <Affinity> <Subprocess 1 priority> <Subprocess 2 priority>\n"));
	_tprintf_s(_T("Affinity: Number which binary representation show which cores of CPU can be used by process.\n"));
	_tprintf_s(_T("Priority: Realtime - %u\n"), REALTIME_PRIORITY_CLASS);
	_tprintf_s(_T("	  High - %u\n"), HIGH_PRIORITY_CLASS);
	_tprintf_s(_T("	  Above normal - %u\n"), ABOVE_NORMAL_PRIORITY_CLASS);
	_tprintf_s(_T("	  Normal - %u\n"), NORMAL_PRIORITY_CLASS);
	_tprintf_s(_T("	  Below normal - %u\n"), BELOW_NORMAL_PRIORITY_CLASS);
	_tprintf_s(_T("	  Idle - %u\n"), IDLE_PRIORITY_CLASS);
}