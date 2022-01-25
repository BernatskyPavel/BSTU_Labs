#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main()
{
  __pid_t pid = getpid();
  for (size_t i = 0; i < 100; i++) {
    printf("PID: %d - %zu\n", pid, i + 1);
    if (i == 24) {
      system("./Lab-03-06x");
    }
    sleep(1);
  }
  return 0;
}
