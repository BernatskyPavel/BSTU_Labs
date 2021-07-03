#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <wchar.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>

int main() {

    struct timespec cpu;
    struct timespec real_start, real_end;
    clock_gettime(CLOCK_REALTIME, &real_start);
    size_t iterations = 0;

    for(;;){
        iterations+=1;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu);
        if(cpu.tv_sec >= 2){
            clock_gettime(CLOCK_REALTIME, &real_end);
            break;
        }
    }

    double time = 0.0;
    time = (real_end.tv_sec - real_start.tv_sec);
    time += (real_end.tv_nsec - real_start.tv_nsec) / 1.0e9;

    wprintf(L"Processor time: %1.9f, Real time: %1.9f, Iterations: %zu\n", cpu.tv_sec + cpu.tv_nsec /1.0e9, time, iterations);

    return 0;
}
