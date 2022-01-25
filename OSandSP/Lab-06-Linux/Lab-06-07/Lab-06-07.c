#include <malloc.h>
#include <stdio.h>
#include <unistd.h>

#define KB 1024
#define MB 1024 * KB

int
main()
{
  printf("Process %d start working!\n", getpid());

  int size = 256 * MB;
  int* array = (int*)malloc(size);

  printf("Address of array: %p!\n", array);

  for (size_t i = 0; i < size / sizeof(int); i++) {
    array[i] = i;
  };

  sleep(60);
  free(array);
  printf("Process end working!\n");
  return 0;
}
