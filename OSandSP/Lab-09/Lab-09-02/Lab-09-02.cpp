// Lab-09-02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>

#define KB 1024
#define MB 1024 * KB
#define MAX_NAME 2048

typedef BOOL(CALLBACK* PRINTTXT)(LPWSTR);

size_t length(std::wstring* str) {
	size_t length = 0;
	for (auto iter = str->begin(); iter != str->end(); iter++) {
		if (*iter == L'\0') break;
		length++;
	}
	return length;
}

BOOL delRowFileTxt(LPWSTR FileName, DWORD row) {

	if (row == 0) {
		return FALSE;
	}

	HANDLE h_file = CreateFileW(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (h_file == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	std::wstring buffer;
	buffer.resize(MB, L'\0');
	DWORD dw_bytesread;

	BOOL result = ReadFile(h_file, &buffer[0], (DWORD)buffer.size(), &dw_bytesread, NULL);
	CloseHandle(h_file);
	
	if (result == FALSE) {
		return FALSE;
	}

	size_t row_counter = 0, i = 0;
	std::wstring::iterator start, end;
	bool is_tracking = false, is_ended = false;

	for (auto iter = ++buffer.begin(); iter != buffer.end(); iter++) {
		if (!is_tracking && (row - 1) == row_counter) {
			start = iter;
			is_tracking = true;
		}
		if (*iter == L'\n') {
			row_counter += 1;
			if (row_counter == row) {
				is_ended = true;
				end = ++iter;
				break;
			}
		}
	}

	if ((row - 1) > row_counter) {
		return FALSE;
	}

	if (is_ended) {
		buffer.erase(start, end);
	}
	else {
		buffer.erase(start, buffer.end());
	}

	h_file = CreateFileW(FileName, GENERIC_WRITE, NULL, NULL, TRUNCATE_EXISTING, NULL, NULL);
	if (h_file == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	DWORD dw_byteswritten;
	result = WriteFile(h_file, buffer.c_str(), sizeof(wchar_t)*(DWORD)length(&buffer), &dw_byteswritten, NULL);
	if (result == FALSE) {
		CloseHandle(h_file);
		return FALSE;
	}

	CloseHandle(h_file);
	return TRUE;
}

int wmain(int argc, wchar_t** argv)
{
	int _ = _setmode(_fileno(stdout), _O_U16TEXT);

	if (argc < 2) {
		std::wcout << L"File not specified!\n";
		return 1;
	}

	DWORD rows[] = { 1, 3, 8 ,10 };
	BOOL result;
	for (size_t i = 0; i < sizeof(rows) / sizeof(rows[0]); i++) {
		result = delRowFileTxt(argv[1], rows[i]);
		if (result) {
			std::wcout << L"Row " << rows[i] << L" deleted successfully!\n";
		}
		else {
			std::wcout << L"Row " << rows[i] << L" is not deleted because "
				<< (GetLastError() == 0 ?
					L"there is no row with such number!\n"
					: L"there is some internal error occured!\n");
		}
		Sleep(1000);
	}

	if (argc < 3) {
		std::wcout << L"Dll for printing not specified!\n";
		return 1;
	}
	if (argc < 4) {
		std::wcout << L"Method from Dll for printing not specified!\n";
		return 1;
	}
	HMODULE h_module = LoadLibraryW(argv[2]);
	if (h_module == NULL) {
		std::wcout << L"Error while loading DLL: " << GetLastError() << L"\n";
		return 1;
	}

	char* proc_name = new char[MAX_NAME];
	size_t actual_length;
	errno_t err_res = wcstombs_s(&actual_length, proc_name, (size_t)MAX_NAME, (const wchar_t*)argv[3], (size_t)MAX_NAME);

	if (err_res != NULL) {
		std::wcout << L"Error while translating proc name: " << GetLastError() << L"\n";
		FreeLibrary(h_module);
		delete[] proc_name;
		return 1;
	}

	PRINTTXT print = (PRINTTXT)GetProcAddress(h_module, proc_name);

	if (print == NULL) {
		std::wcout << L"Error while recieving proc: " << GetLastError() << L"\n";
		FreeLibrary(h_module);
		delete[] proc_name;
		return 1;
	}

	print(argv[1]);

	FreeLibrary(h_module);
	delete[] proc_name;
	return 0;
}