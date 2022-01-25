#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int
main()
{
  __pid_t pid = getpid();
  for (size_t i = 0; i < 50; i++) {
    printf("PID: %d - %zu\n", pid, i + 1);
    sleep(1);
  }
  return 0;
}
