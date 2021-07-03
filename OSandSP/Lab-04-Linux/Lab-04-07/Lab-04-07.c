#define _GNU_SOURCE
#include <stdio.h>
#include <wchar.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

void* Lab_04_07_01(void* arg){
    __pid_t pid = getpid();
    __pid_t tid = gettid();
    for(size_t i = 0; i < 75; i++){
        wprintf(L"Pid: %d, Tid: %d, %d\n", pid, tid, i+1);
        sleep(1);
    }
}

int main() {
    __pid_t pid = getpid();
    __pid_t tid = gettid();

    pthread_t thread;
    if(pthread_create(&thread, NULL, Lab_04_07_01, NULL) != 0) {
        wprintf(L"pthread_create failed: %s\n", strerror(errno));
        return 1;
    }

    for(size_t i = 0; i < 100; i++){
        wprintf(L"Pid: %d, Tid: %d, %d\n", pid, tid, i+1);
        sleep(1);
    }

    pthread_join(thread, NULL);

    return 0;
}

/*
 *if (execl("./Lab-03-07x", "", (char *)NULL) == -1) {
                wprintf(L"Exec error: %s\n", strerror(errno));

 */
