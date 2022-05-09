#include "extra.hpp"
#include "lab_08.hpp"
#include <cwchar>
#include <iostream>
#include <locale>
#include <sys/ioctl.h>

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

  task extra[] = { extra::first_extra,
                   extra::second_extra,
                   extra::third_extra,
                   extra::fourth_extra,
                   extra::fifth_extra };

  for (;;) {
  outer:
    std::wcout << std::endl;
    system("clear");
    std::wcout << L"Please select task:\n1)Part one (16 "
                  L"tasks).\n2)Extra (5 tasks)\n0)Exit\nYour choice is ";
    int choice;
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
              variants[choice - 1]();
              break;
            case 0:
              goto outer;
              break;
            default:
              break;
          }
        }
        break;
      case 2:
        for (;;) {
          std::wcout
            << L"Please input number of extra (1-5, 0 or letter - exit):";
          int choice;
          std::wcin >> choice;
          switch (choice) {
            case 1 ... 5:
              std::wcout << std::endl;
              system("clear");
              std::wcout << L"Extra " << choice << L":\n";
              extra[choice - 1]();
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
