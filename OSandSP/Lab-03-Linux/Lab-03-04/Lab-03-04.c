#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int
main()
{
  __pid_t pid = getpid();
  for (size_t i = 0; i < 1000; i++) {
    printf("PID: %d - %zu\n", pid, i + 1);
    sleep(2);
  }
  return 0;
}
