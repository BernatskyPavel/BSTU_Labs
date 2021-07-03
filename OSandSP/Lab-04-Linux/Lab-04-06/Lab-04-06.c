#define _GNU_SOURCE
#include <stdio.h>
#include <wchar.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    __pid_t pid = getpid();
    __pid_t tid = gettid();
    for(size_t i = 0; i < 1000; i++){
        wprintf(L"Pid: %d, Tid: %d, %d\n", pid, tid, i+1);
        sleep(1);
    }
    return 0;
}
