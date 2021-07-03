#include <stdio.h>
#include <wchar.h>
#include <unistd.h>
#include <malloc.h>

int main() {

    wprintf(L"Process %d start working!\n", getpid());

    int size = 256*1024*1024;
    int* array = (int*)malloc(size);

    wprintf(L"Address of array: %p!\n", array);

    for(size_t i = 0; i < size/sizeof(int); i++) {

        array[i] = i;
    };

    sleep(60);
    free(array);
    wprintf(L"Process end working!\n");
    return 0;
}
