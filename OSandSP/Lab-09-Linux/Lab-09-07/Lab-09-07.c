#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>

#define BUFFER_SIZE 512
#define OFFSET 8
#define SUB 8

int
main()
{
  int file = open("OS09_07.txt", O_RDONLY);
  if (file == -1) {
    printf("File opening failed with error %d\n", errno);
    exit(-1);
  }

  off_t offset = lseek(file, OFFSET, SEEK_SET);

  if (offset == -1) {
    close(file);
    printf("File opening failed with error %d\n", errno);
    exit(-1);
  }

  char buffer[BUFFER_SIZE];
  ssize_t readlen;
  while ((readlen = read(file, buffer, SUB)) > 0) {
    printf("Next 8-bytes is %s\n", buffer);
    offset = lseek(file, OFFSET, SEEK_CUR);
    if (offset == -1) {
      close(file);
      printf("File opening failed with error %d\n", errno);
      exit(-1);
    }
  }

  if (readlen < 0)
    printf("File reading failed with error %d\n", errno);

  close(file);
  exit(0);
}
