#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#define ARRAY_SIZE 300000
#define KB 1024
#define MB KB*1024

void sh(HANDLE);

int _tmain(void)
{
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE, 4 * MB, 0 * MB);
	if (heap == INVALID_HANDLE_VALUE || heap == NULL) {
		_tprintf_s(_T("HeapCreate failed (%u)\n"), GetLastError());
		return 1;
	}
	_tprintf_s(_T("Size and structure of heap as the begining:\n"));
	sh(heap);
	_tsystem(_T("pause & cls"));
	int* arr = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, sizeof(int) * ARRAY_SIZE);
	if (arr == NULL) {
		_tprintf_s(_T("HeapAlloc failed (%u)\n"), GetLastError());
		BOOL result = HeapDestroy(heap);
		if (!result) {
			_tprintf_s(_T("HeapDestroy failed (%u)\n"), GetLastError());
		}

		CloseHandle(heap);
		return 2;
	}
	for (int i = 0; i < ARRAY_SIZE; i++) {
		arr[i] = i;
	}

	_tprintf_s(_T("Size and structure of heap after creating of array:\n"));
	sh(heap);
	_tsystem(_T("pause & cls"));

	BOOL result = HeapFree(heap, HEAP_NO_SERIALIZE, (LPVOID)arr);
	if (!result) {
		_tprintf_s(_T("HeapFree failed (%u)\n"), GetLastError());
	}

	_tprintf_s(_T("Size and structure of heap after removing of array:\n"));
	sh(heap);
	_tsystem(_T("pause & cls"));
	
	result = HeapDestroy(heap);
	if (!result) {
		_tprintf_s(_T("HeapDestroy failed (%u)\n"), GetLastError());
	}

	CloseHandle(heap);

}

void sh(HANDLE heap) {
	if (heap == INVALID_HANDLE_VALUE || heap == NULL) {
		_tprintf_s(_T("Invalid or empty handle!"));
		return;
	}
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(heap, &phe)) {
		_tprintf_s(_T("Address: %p, "), phe.lpData);
		_tprintf_s(_T("size: %u, "), phe.cbData);
		LPCTSTR type;
		switch (phe.wFlags) {
		case PROCESS_HEAP_REGION: type = _T("REG"); break;
		case PROCESS_HEAP_UNCOMMITTED_RANGE: type = _T("URNG"); break;
		case PROCESS_HEAP_ENTRY_BUSY: type = _T("BSY"); break;
		case PROCESS_HEAP_SEG_ALLOC: type = _T("SEGA"); break;
		case PROCESS_HEAP_ENTRY_DDESHARE: type = _T("EDS"); break;
		case PROCESS_HEAP_ENTRY_MOVEABLE: type = _T("EMV"); break;
		default: type = _T("OTH"); break;
		}
		_tprintf_s(_T("type: %s\n"), type);
	}
}