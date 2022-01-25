#include <stdio.h>
#include <unistd.h>

int
main()
{

  __pid_t pid = getpid();
  printf("Process %d start working!\n", pid);
  for (size_t i = 0; i < 1000; i++) {
    printf("(%d) Iteration -> %ld!\n", pid, i + 1);
    sleep(1);
  }
  printf("Process end working!\n");
  return 0;
}
