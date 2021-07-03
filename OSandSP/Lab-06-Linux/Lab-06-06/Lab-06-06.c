#include <stdio.h>
#include <wchar.h>
#include <unistd.h>

int main() {

    wprintf(L"Process %d start working!\n", getpid());
    for(size_t i = 0; i < 1000; i++) {
        sleep(1);
    }
    wprintf(L"Process end working!\n");
    return 0;
}
