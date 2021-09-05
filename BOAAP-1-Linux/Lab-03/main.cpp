#include "lab_03.h"
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
    first_variant,      second_variant,     third_variant,
    fourth_variant,     fifth_variant,      sixth_variant,
    seventh_variant,    eighth_variant,     ninth_variant,
    tenth_variant,      eleventh_variant,   twelfth_variant,
    thirteenth_variant, fourteenth_variant, fifteenth_variant,
    sixteenth_variant,
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
