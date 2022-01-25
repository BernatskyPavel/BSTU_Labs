#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void*
Lab_04_07_01(void* arg)
{
  __pid_t pid = getpid();
  __pid_t tid = gettid();
  for (size_t i = 0; i < 75; i++) {
    printf("Pid: %d, Tid: %d, %ld\n", pid, tid, i + 1);
    sleep(1);
  }
}

int
main()
{
  __pid_t pid = getpid();
  __pid_t tid = gettid();

  pthread_t thread;
  if (pthread_create(&thread, NULL, Lab_04_07_01, NULL) != 0) {
    printf("pthread_create failed: %s\n", strerror(errno));
    return 1;
  }

  for (size_t i = 0; i < 100; i++) {
    printf("Pid: %d, Tid: %d, %ld\n", pid, tid, i + 1);
    sleep(1);
  }

  pthread_join(thread, NULL);

  return 0;
}
