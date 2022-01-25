#include <stdio.h>
#include <tchar.h>
#include <time.h>

volatile unsigned counter;

int
_tmain()
{
  bool step1 = false, step2 = false;
  clock_t start = clock();
  while(true) {
    counter += 1;
    double diff = (static_cast<double>(clock()) - static_cast<double>(start)) /
                  CLOCKS_PER_SEC;
    if (!step1 && diff >= 5.0) {
      _tprintf_s(_T("Iteration counter after 5 seconds: %u\n"), counter);
      step1 = true;
      continue;
    }
    if (!step2 && diff >= 10.0) {
      _tprintf_s(_T("Iteration counter after 10 seconds: %u\n"), counter);
      step2 = true;
      continue;
    }
    if (diff >= 15.0) {
      _tprintf_s(_T("Iteration counter after 15 seconds: %u\n"), counter);
      break;
    }
  }
}
