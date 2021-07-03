#define _GNU_SOURCE
#include <stdio.h>
#include <wchar.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

pthread_mutex_t mutex;

void* Lab_07_06_01(void* arg){
    __pid_t pid = getpid();
    __pid_t tid = gettid();
    for(size_t i = 0; i < 90; i++){
        if(i==29) {
            pthread_mutex_lock(&mutex);
        }
        if(i==59) {
            pthread_mutex_unlock(&mutex);
        }
        wprintf(L"Pid: %d, Tid: %d, %d\n", pid, tid, i+1);
        usleep(100000);
    }
}

int main() {
    __pid_t pid = getpid();
    __pid_t tid = gettid();

    if(pthread_mutex_init(&mutex, NULL) != 0){
        wprintf(L"pthread_mutex_init failed: %s\n", strerror(errno));
        return 1;
    }

    pthread_t thread_1, thread_2;
    if(pthread_create(&thread_1, NULL, Lab_07_06_01, NULL) != 0) {
        wprintf(L"pthread_create failed: %s\n", strerror(errno));
        return 1;
    }

    if(pthread_create(&thread_2, NULL, Lab_07_06_01, NULL) != 0) {
        wprintf(L"pthread_create 2 failed: %s\n", strerror(errno));
        return 1;
    }

    for(size_t i = 0; i < 90; i++){
        if(i==29) {
            pthread_mutex_lock(&mutex);
        }
        if(i==59) {
            pthread_mutex_unlock(&mutex);
        }
        wprintf(L"Pid: %d, Tid: %d, %d\n", pid, tid, i+1);
        usleep(100000);
    }

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
