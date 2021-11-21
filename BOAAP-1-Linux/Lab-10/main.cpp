#include "lab_10.hpp"
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
    lab_10::first_variant,      lab_10::second_variant,
    lab_10::third_variant,      lab_10::fourth_variant,
    lab_10::fifth_variant,      lab_10::sixth_variant,
    lab_10::seventh_variant,    lab_10::eighth_variant,
    lab_10::ninth_variant,      lab_10::tenth_variant,
    lab_10::eleventh_variant,   lab_10::twelfth_variant,
    lab_10::thirteenth_variant, lab_10::fourteenth_variant,
    lab_10::fifteenth_variant,  lab_10::sixteenth_variant,
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
