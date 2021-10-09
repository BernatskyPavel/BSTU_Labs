#include "extra.hpp"
#include "lab_04.hpp"
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
    lab_04::first_variant,      lab_04::second_variant,
    lab_04::third_variant,      lab_04::fourth_variant,
    lab_04::fifth_variant,      lab_04::sixth_variant,
    lab_04::seventh_variant,    lab_04::eighth_variant,
    lab_04::ninth_variant,      lab_04::tenth_variant,
    lab_04::eleventh_variant,   lab_04::twelfth_variant,
    lab_04::thirteenth_variant, lab_04::fourteenth_variant,
    lab_04::fifteenth_variant,  lab_04::sixteenth_variant,
  };

  task extra[] = {
    extra::first_extra,   extra::second_extra, extra::third_extra,
    extra::fourth_extra,  extra::fifth_extra,  extra::sixth_extra,
    extra::seventh_extra, extra::eighth_extra, extra::ninth_extra,
    extra::tenth_extra,
  };

  for (;;) {
  outer:
    std::wcout << std::endl;
    system("clear");
    std::wcout
      << L"Please select task:\n1)Part one (16 "
         L"tasks).\n2)Dialog\n3)Extra (10 tasks)\n0)Exit\nYour choice is ";
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
        std::wcout << std::endl;
        system("clear");
        std::wcout << L"Dialog:\n";
        lab_04::dialog();
        break;
      case 3:
        for (;;) {
          std::wcout
            << L"Please input number of extra (1-10, 0 or letter - exit):";
          int choice;
          std::wcin >> choice;
          switch (choice) {
            case 1 ... 10:
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
