#include <stdio.h>
#include <wchar.h>
#include <unistd.h>

int main() {

    __pid_t pid = getpid();
    wprintf(L"Process %d start working!\n", pid);
    for(size_t i = 0; i < 1000; i++) {
        wprintf(L"(%d) Iteration -> %d!\n", pid, i+1);
        sleep(1);
    }
    wprintf(L"Process end working!\n");
    return 0;
}
