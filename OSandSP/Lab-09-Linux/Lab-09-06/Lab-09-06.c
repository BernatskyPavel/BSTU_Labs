#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 64

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Missing argument! (Use: ./Lab-09-06 <int>)\n");
    exit(-1);
  }

  int num = 0;
  if ((num = atoi(argv[1])) == 0) {
    printf("Invalid argument! (Use: ./Lab-09-06 <int>)\n");
    exit(-1);
  }

  int read_file = open("OS09_06.txt", O_RDONLY);
  if (read_file == -1) {
    printf("File opening failed with error %d\n", errno);
    exit(-1);
  }

  bool is_odd = (num % 2 != 0);

  char* filename = is_odd ? "OS09_06_01.txt" : "OS09_06_02.txt";
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int write_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
  if (write_file == -1) {
    printf("File creating failed with error %d\n", errno);
    close(read_file);
    exit(-1);
  }

  char buffer[BUFFER_SIZE], write_buffer[BUFFER_SIZE];
  ssize_t readlen, writelen;
  size_t rows = 0, to_write = 0;
  bool is_writable = false;
  while ((readlen = read(read_file, buffer, sizeof(buffer))) > 0) {
    for (int i = 0; i < readlen; i++) {
      if (is_writable) {
        if (rows % 2 == is_odd) {
          writelen = write(write_file, write_buffer, to_write);
          if (writelen < 0) {
            printf("File writing failed with error %d\n", errno);
            close(read_file);
            close(write_file);
            exit(-1);
          }
        }
        to_write = 0;
        is_writable = false;
      }
      if (buffer[i] == '\n') {
        rows += 1;
        is_writable = true;
      }
      write_buffer[to_write++] = buffer[i];
    }
  }

  if (readlen < 0)
    printf("File reading failed with error %d\n", errno);
  if (to_write != 0 && rows % 2 == is_odd) {
    writelen = write(write_file, write_buffer, to_write);
    if (writelen < 0)
      printf("File writing failed with error %d\n", errno);
  }

  close(read_file);
  close(write_file);
  exit(0);
}
