#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>

int main() {
    printf("Size of time_t: %ld bytes (%ld bits)\n", sizeof(time_t), sizeof(time_t) * 8);

    
    long long max_seconds;
    
    if (sizeof(time_t) == 4) {
        max_seconds = 2147483647;
        printf("Architecture: 32-bit time_t equivalent\n");
    } else {
        max_seconds = 9223372036854775807;
        printf("Architecture: 64-bit time_t equivalent\n");
    }

    printf("Max timestamp value: %lld\n", max_seconds);

    time_t raw_time = (time_t)max_seconds;
    struct tm * time_info = gmtime(&raw_time);

    if (time_info != NULL) {
        printf("End of time date (UTC): %s", asctime(time_info));
    } else {
        printf("Date is too far in the future to display!\n");
    }

    return 0;
}