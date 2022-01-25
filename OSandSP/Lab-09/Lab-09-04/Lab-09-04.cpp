#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

#define KB 1024
#define MB 1024 * KB

HANDLE h_dir;
size_t row_counter = 0;
int stop = 0;

size_t
count_rows_in_file(LPCWSTR FileName)
{
  size_t rows = 0;
  HANDLE h_file = CreateFileW(
    FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
  if (h_file == INVALID_HANDLE_VALUE) {
    return 0;
  }

  std::wstring buffer;
  buffer.resize(MB, L'\0');
  DWORD dw_bytesread;

  BOOL result =
    ReadFile(h_file, &buffer[0], (DWORD)buffer.size(), &dw_bytesread, NULL);
  CloseHandle(h_file);
  if (result == FALSE) {
    return 0;
  }

  for (auto iter = buffer.begin(); iter != buffer.end(); iter++) {
    if (*iter == L'\n') {
      rows += 1;
    }
  }
  buffer.clear();
  return rows + 1;
}

void
waiter(int mlsec)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(mlsec));
  stop = 1;
  return;
}

void
thread_func(std::wstring& file, LPCWSTR FileName)
{
  OVERLAPPED overlp;
  overlp.hEvent = CreateEventW(NULL, FALSE, 0, NULL);

  if (overlp.hEvent == NULL || overlp.hEvent == INVALID_HANDLE_VALUE) {
    std::wcout << L"Attempt to create event handle failed!\n";
    return;
  }

  uint8_t change_buf[1024];
  BOOL result = ReadDirectoryChangesW(h_dir,
                                      change_buf,
                                      1024,
                                      TRUE,
                                      FILE_NOTIFY_CHANGE_LAST_WRITE,
                                      NULL,
                                      &overlp,
                                      NULL);

  while (stop == 0) {
    DWORD wait_status = WaitForSingleObject(overlp.hEvent, 1000);

    if (wait_status == WAIT_OBJECT_0) {
      DWORD bytes_transferred;
      GetOverlappedResult(h_dir, &overlp, &bytes_transferred, FALSE);

      FILE_NOTIFY_INFORMATION* event = (FILE_NOTIFY_INFORMATION*)change_buf;

      for (;;) {
        DWORD name_len = event->FileNameLength / sizeof(wchar_t);
        switch (event->Action) {
          case FILE_ACTION_MODIFIED: {
            std::wstring name_buff;
            name_buff.resize((size_t)name_len + 1);
            swprintf_s(&name_buff[0],
                       (size_t)name_len + 1,
                       L"%.*s",
                       name_len,
                       event->FileName);
            if (name_buff.compare(file) == 0) {
              size_t temp = count_rows_in_file(FileName);
              if (row_counter == temp) {
                std::wcout << L"Number of rows in file " << file
                           << L" doesn't change!\n";
              } else {
                std::wcout << L"Number of rows in file " << file
                           << L" changed from " << row_counter << L" to "
                           << temp << L"!\n";
                row_counter = temp;
              }
            }
          } break;
          default:
            break;
        }
        if (event->NextEntryOffset) {
          *((uint8_t**)&event) += event->NextEntryOffset;
        } else {
          break;
        }
      }

      BOOL result = ReadDirectoryChangesW(h_dir,
                                          change_buf,
                                          1024,
                                          TRUE,
                                          FILE_NOTIFY_CHANGE_LAST_WRITE,
                                          NULL,
                                          &overlp,
                                          NULL);
    }
  }
  return;
}

BOOL
printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec)
{
  row_counter = count_rows_in_file(FileName);

  std::wstring path = std::wstring(FileName);
  std::wstring file, dir;
  if (path.find_first_of(L"/\\") != std::wstring::npos) {
    std::wstring::size_type found = path.find_last_of(L"/\\");
    dir = path.substr(0, found);
    file = path.substr(found + 1);
    file.resize(file.size() + 1, L'\0');
  } else {

    DWORD size = GetCurrentDirectoryW(0, NULL);
    dir.resize(size);
    size = GetCurrentDirectoryW(size, &dir[0]);
    file = path;
    file.resize(file.size() + 1, L'\0');
  }

  h_dir = CreateFileW(dir.c_str(),
                      FILE_LIST_DIRECTORY,
                      FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
                      NULL,
                      OPEN_EXISTING,
                      FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
                      NULL);

  if (h_dir == INVALID_HANDLE_VALUE || h_dir == NULL) {
    std::wcout << L"Attempt to open the directory failed!\n";
    return FALSE;
  }
  std::wcout << L"Start watching...\n";
  std::thread thread(thread_func, std::ref(file), FileName),
    wait(waiter, mlsec);
  wait.join();
  thread.join();
  std::wcout << L"Stop watching!\n";
  CloseHandle(h_dir);
  return TRUE;
}

int
wmain(int argc, wchar_t** argv)
{
  int _ = _setmode(_fileno(stdout), _O_U16TEXT);
  if (argc < 2) {
    std::wcout << L"File not specified!\n";
    return 1;
  }
  if (argc < 3) {
    std::wcout << L"Time to wait is not specified!\n";
    return 1;
  }
  int mlsec = _wtoi(argv[2]);
  printWatchRowFileTxt(argv[1], mlsec);
}
