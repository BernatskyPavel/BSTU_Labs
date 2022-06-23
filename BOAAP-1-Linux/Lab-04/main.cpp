#include "lab_04.hpp"
#include <cwchar>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

typedef void (*variant)();
struct winsize win_size;

int
main()
{
  std::locale::global(std::locale("ru_RU.utf-8"));

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);

  variant variants[] = {
    lab_04::first_variant,      lab_04::second_variant,
    lab_04::third_variant,      lab_04::fourth_variant,
    lab_04::fifth_variant,      lab_04::sixth_variant,
    lab_04::seventh_variant,    lab_04::eighth_variant,
    lab_04::ninth_variant,      lab_04::tenth_variant,
    lab_04::eleventh_variant,   lab_04::twelfth_variant,
    lab_04::thirteenth_variant, lab_04::fourteenth_variant,
    lab_04::fifteenth_variant,  lab_04::sixteenth_variant,
  };

  for (;;) {
    std::wcout << L"Please input number of variant (1-16, 0 or letter - exit):";
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
        goto exit;
        break;
      default:
        break;
    }
  }
exit:
  return 0;
}
