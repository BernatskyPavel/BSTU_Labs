#include <stdio.h>
#include <unistd.h>

int
main()
{

  printf("Process %d start working!\n", getpid());
  for (size_t i = 0; i < 1000; i++) {
    sleep(1);
  }
  printf("Process end working!\n");
  return 0;
}
