#define _GNU_SOURCE
#include <stdio.h>
#include <wchar.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

int main() {
    __pid_t pid = getpid();
    __pid_t tid = gettid();

    wprintf(L"Pid: %d, Tid: %d, Nice: %d\n", pid, tid, getpriority(PRIO_PROCESS, pid));

    cpu_set_t affinity;
    if(sched_getaffinity(0, sizeof(cpu_set_t), &affinity) == -1) {
        wprintf(L"sched_getaffinity failed: %s\n", strerror(errno));
        return 1;
    } else {
        size_t i = 0;
        for(;;){
            if(CPU_ISSET(i, &affinity)){
                wprintf(L"CPU %d is available\n", i++);
            } else{
                break;
            }
        }
    };
    return 0;
}
