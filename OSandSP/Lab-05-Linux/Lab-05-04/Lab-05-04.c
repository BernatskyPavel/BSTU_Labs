#define _GNU_SOURCE
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wchar.h>

int
main()
{
  __pid_t pid = getpid();
  __pid_t tid = gettid();

  printf(
    "Pid: %d, Tid: %d, Nice: %d\n", pid, tid, getpriority(PRIO_PROCESS, pid));

  cpu_set_t affinity;
  if (sched_getaffinity(0, sizeof(cpu_set_t), &affinity) == -1) {
    printf("sched_getaffinity failed: %s\n", strerror(errno));
    return 1;
  } else {
    size_t i = 0;
    while (i < 1024) {
      if (CPU_ISSET(i, &affinity)) {
        printf("CPU %ld is available\n", i);
      }
      i++;
    }
  };
  return 0;
}
