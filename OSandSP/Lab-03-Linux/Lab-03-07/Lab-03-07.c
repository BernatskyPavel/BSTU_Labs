#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int
main()
{
  __pid_t pid = getpid();
  for (size_t i = 0; i < 100; i++) {
    printf("PID: %d - %zu\n", pid, i + 1);
    if (i == 24) {
      if (execl("./Lab-03-07x", "", (char*)NULL) == -1) {
        printf("Exec error: %s\n", strerror(errno));
      }
    }
    sleep(1);
  }
  return 0;
}
