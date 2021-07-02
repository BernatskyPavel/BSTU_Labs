#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <tchar.h>

int _tmain()
{
    DWORD pid = GetCurrentProcessId();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 peProcessEntry;
    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &peProcessEntry)) {
        _tprintf_s(_T("Process32First failed (%u)\n"), GetLastError());
        CloseHandle(hSnapshot);
        return 1;
    }
    do {
        _tprintf_s(_T("Process %s (%u), Parent (%u)\n"), peProcessEntry.szExeFile, peProcessEntry.th32ProcessID, peProcessEntry.th32ParentProcessID);
        if (peProcessEntry.th32ProcessID == pid) {
            _tprintf_s(_T("         ^\n"));
            _tprintf_s(_T("         |\n"));
            _tprintf_s(_T("         |______ CURRENT PROCESS!\n"));
        }
        _tprintf_s(_T("--------------------------\n"));
    } while (Process32Next(hSnapshot, &peProcessEntry));

    _tsystem(_T("pause"));
    return 0;
}
