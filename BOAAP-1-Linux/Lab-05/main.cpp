#include "extra.hpp"
#include "lab_05.hpp"
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
    lab_05::first_variant,      lab_05::second_variant,
    lab_05::third_variant,      lab_05::fourth_variant,
    lab_05::fifth_variant,      lab_05::sixth_variant,
    lab_05::seventh_variant,    lab_05::eighth_variant,
    lab_05::ninth_variant,      lab_05::tenth_variant,
    lab_05::eleventh_variant,   lab_05::twelfth_variant,
    lab_05::thirteenth_variant, lab_05::fourteenth_variant,
    lab_05::fifteenth_variant,  lab_05::sixteenth_variant,
  };

  task extra[] = {
    extra::first_extra,   extra::second_extra, extra::third_extra,
    extra::fourth_extra,  extra::fifth_extra,  extra::sixth_extra,
    extra::seventh_extra, extra::eighth_extra,
  };

  for (;;) {
  outer:
    std::wcout << std::endl;
    system("clear");
    std::wcout << L"Please select task:\n1)Part one (16 "
                  L"tasks).\n2)Extra (8 tasks)\n0)Exit\nYour choice is ";
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
            << L"Please input number of extra (1-8, 0 or letter - exit):";
          int choice;
          std::wcin >> choice;
          switch (choice) {
            case 1 ... 8:
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
