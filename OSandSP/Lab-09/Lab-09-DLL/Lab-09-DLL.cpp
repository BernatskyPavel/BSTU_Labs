#include "Lab-09-DLL.h"
#include <iostream>
#include <stdio.h>

#define KB 1024
#define MB 1024 * KB

namespace Lab_09_DLL {
BOOL
printFileInfo(LPWSTR FileName)
{
  HANDLE h_file =
    CreateFileW(FileName, NULL, NULL, NULL, OPEN_EXISTING, NULL, NULL);
  if (h_file != INVALID_HANDLE_VALUE) {
    WIN32_FIND_DATA f_data;
    HANDLE h_search = FindFirstFile(FileName, &f_data);
    if (h_search == INVALID_HANDLE_VALUE) {
      return FALSE;
    }
    SYSTEMTIME tm_creation, tm_modefied;
    FileTimeToSystemTime(&f_data.ftCreationTime, &tm_creation);
    FileTimeToSystemTime(&f_data.ftLastWriteTime, &tm_modefied);
    DWORD f_size =
      (f_data.nFileSizeHigh * (MAXDWORD + 1)) + f_data.nFileSizeLow;
    DWORD type = GetFileType(h_file);
    CloseHandle(h_file);
    wprintf_s(L"File information: \n");
    wprintf_s(L" - File name: %s\n", f_data.cFileName);
    LPCTSTR t_type;
    switch (type) {
      case FILE_TYPE_CHAR:
        t_type = L"Character";
        break;
      case FILE_TYPE_DISK:
        t_type = L"Disk";
        break;
      case FILE_TYPE_PIPE:
        t_type = L"Socket/Pipe";
        break;
      case FILE_TYPE_REMOTE:
        t_type = L"Remote";
        break;
      case FILE_TYPE_UNKNOWN:
        t_type = L"Unknown";
        break;
      default:
        t_type = L"Mystery";
        break;
    }
    wprintf_s(L" - File type: %s\n - File size: %u bytes\n", t_type, f_size);
    wprintf_s(L" - File creation date and time: %02i.%02i.%i %02i:%02i:%02i\n",
              tm_creation.wDay,
              tm_creation.wMonth,
              tm_creation.wYear,
              tm_creation.wHour,
              tm_creation.wMinute,
              tm_creation.wSecond);
    wprintf_s(
      L" - File last modification date and time: %02i.%02i.%i %02i:%02i:%02i\n",
      tm_modefied.wDay,
      tm_modefied.wMonth,
      tm_modefied.wYear,
      tm_modefied.wHour,
      tm_modefied.wMinute,
      tm_modefied.wSecond);
  } else {
    return FALSE;
  }
  return TRUE;
}

BOOL
printFileText(LPWSTR FileName)
{
  HANDLE h_file =
    CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
  if (h_file == INVALID_HANDLE_VALUE || h_file == NULL) {
    return FALSE;
  }

  std::wstring buffer;
  buffer.resize(MB, L'\0');
  DWORD dw_bytesread;

  BOOL result =
    ReadFile(h_file, &buffer[0], (DWORD)buffer.size(), &dw_bytesread, NULL);
  CloseHandle(h_file);
  if (result == FALSE) {
    return FALSE;
  }
  std::wcout << L"File text:\r\n" << buffer.c_str() << std::endl;

  return TRUE;
}
}