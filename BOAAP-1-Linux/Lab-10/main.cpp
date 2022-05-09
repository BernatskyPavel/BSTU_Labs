#include "extra.hpp"
#include "lab_10.hpp"
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
    lab_10::first_variant,      lab_10::second_variant,
    lab_10::third_variant,      lab_10::fourth_variant,
    lab_10::fifth_variant,      lab_10::sixth_variant,
    lab_10::seventh_variant,    lab_10::eighth_variant,
    lab_10::ninth_variant,      lab_10::tenth_variant,
    lab_10::eleventh_variant,   lab_10::twelfth_variant,
    lab_10::thirteenth_variant, lab_10::fourteenth_variant,
    lab_10::fifteenth_variant,  lab_10::sixteenth_variant,
  };

  task extra[] = {
    extra::first_extra,  extra::second_extra, extra::third_extra,
    extra::fourth_extra, extra::fifth_extra,  extra::sixth_extra,
  };

  for (;;) {
  outer:
    std::wcout << std::endl;
    system("clear");
    std::wcout << L"Please select task:\n1)Part one (16 "
                  L"tasks).\n2)Extra (6 tasks)\n0)Exit\nYour choice is ";
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
            << L"Please input number of extra (1-6, 0 or letter - exit):";
          int choice;
          std::wcin >> choice;
          switch (choice) {
            case 1 ... 6:
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
