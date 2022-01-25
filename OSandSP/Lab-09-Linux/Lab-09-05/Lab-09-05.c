#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 512

int
main()
{
  int file = open("OS09_05.txt", O_RDONLY);
  if (file == -1) {
    printf("File opening failed with error %d\n", errno);
    exit(-1);
  }

  char buffer[BUFFER_SIZE];
  ssize_t readlen;
  size_t rows = 0;
  while ((readlen = read(file, buffer, sizeof(buffer))) > 0)
    for (int i = 0; i < readlen; i++)
      if (buffer[i] == '\n')
        rows += 1;

  printf("Number of rows is %ld\n", rows + 1);

  if (readlen < 0)
    printf("File reading failed with error %d\n", errno);

  close(file);
  exit(0);
}
