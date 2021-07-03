#include <stdio.h>
#include <wchar.h>
#include <unistd.h>
#include <time.h>

int main() {

    time_t ut_time = time(NULL);
    struct tm lc_time = *localtime(&ut_time);

    wprintf(L"Current date and time: %02d.%02d.%04d %02d:%02d:%02d.\n", lc_time.tm_mday, lc_time.tm_mon, lc_time.tm_year+1900, lc_time.tm_hour, lc_time.tm_min, lc_time.tm_sec);
    return 0;
}
