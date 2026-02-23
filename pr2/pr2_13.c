#include <stdio.h>

int uninitialized_array[1000];

int initialized_variable = 33;

void function() {
    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        uninitialized_array[i] = i * initialized_variable;
        sum += uninitialized_array[i];
    }
    printf("Sum: %d\n", sum);
}

int main() {
    function();

    return 0;
}