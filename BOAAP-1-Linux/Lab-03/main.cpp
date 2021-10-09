#include "lab_03.hpp"
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
    lab_03::first_variant,      lab_03::second_variant,
    lab_03::third_variant,      lab_03::fourth_variant,
    lab_03::fifth_variant,      lab_03::sixth_variant,
    lab_03::seventh_variant,    lab_03::eighth_variant,
    lab_03::ninth_variant,      lab_03::tenth_variant,
    lab_03::eleventh_variant,   lab_03::twelfth_variant,
    lab_03::thirteenth_variant, lab_03::fourteenth_variant,
    lab_03::fifteenth_variant,  lab_03::sixteenth_variant,
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
