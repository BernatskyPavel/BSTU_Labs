#include "lab_11.hpp"
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
    lab_11::first_variant,      lab_11::second_variant,
    lab_11::third_variant,      lab_11::fourth_variant,
    lab_11::fifth_variant,      lab_11::sixth_variant,
    lab_11::seventh_variant,    lab_11::eighth_variant,
    lab_11::ninth_variant,      lab_11::tenth_variant,
    lab_11::eleventh_variant,   lab_11::twelfth_variant,
    lab_11::thirteenth_variant, lab_11::fourteenth_variant,
    lab_11::fifteenth_variant,  lab_11::sixteenth_variant,
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
