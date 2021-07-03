#define _GNU_SOURCE
#include <stdio.h>
#include <wchar.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

void Lab_03_05_01() {
    __pid_t pid = getpid();
    setpriority(PRIO_PROCESS, 0, getpriority(PRIO_PROCESS, 0)+10);
    for(size_t i = 0; i < 50; i++){
        wprintf(L"PID: %d - %zu\n", pid, i+1);
        sleep(1);
    }
}

int main() {
    switch(fork()){
        case  0: Lab_03_05_01(); break;
        case -1:
            wprintf(L"Fork failed!\n");
            break;
        default:{
            __pid_t pid = getpid();
            for(size_t i = 0; i < 100; i++) {
                wprintf(L"PID: %d - %zu\n", pid, i+1);
                sleep(1);
            }
        }
        break;
    }
    return 0;
}
