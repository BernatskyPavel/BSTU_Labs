#include "lab_08.hpp"
#include <iostream>
#include <locale>
#include <sys/ioctl.h>
#include <wchar.h>

typedef void (*task)();

int
main()
{
  std::locale::global(std::locale("ru_RU.utf-8"));
  std::wcout.setf(std::ios::boolalpha);

  task variants[] = {
    lab_08::first_variant,      lab_08::second_variant,
    lab_08::third_variant,      lab_08::fourth_variant,
    lab_08::fifth_variant,      lab_08::sixth_variant,
    lab_08::seventh_variant,    lab_08::eighth_variant,
    lab_08::ninth_variant,      lab_08::tenth_variant,
    lab_08::eleventh_variant,   lab_08::twelfth_variant,
    lab_08::thirteenth_variant, lab_08::fourteenth_variant,
    lab_08::fifteenth_variant,  lab_08::sixteenth_variant,
  };

  for (;;) {
  outer:
    std::wcout << std::endl;
    system("clear");
    std::wcout << L"Please select task:\n1)Part one (16 "
                  L"tasks).\n0)Exit\nYour choice is ";
    size_t choice;
    std::wcin >> choice;
    switch (choice) {
      case 1:
        for (;;) {
          std::wcout
            << L"Please input number of variant (1-16, 0 or letter - exit):";
          int choice;
          std::wcin >> choice;
          switch (choice) {
            case 1 ... 16:
              std::wcout << std::endl;
              system("clear");
              std::wcout << L"Variant " << choice << L":\n";
              lab_08::general_call(choice);
              break;
            case 0:
              goto outer;
              break;
            default:
              break;
          }
        }
        break;
      case 0:
        goto exit;
        break;
      default:
        break;
    }
  }
exit:
  return 0;
}
