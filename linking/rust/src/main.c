#include <inttypes.h>
#include <stdio.h>

extern uint32_t addition(uint32_t, uint32_t);

int main() {
    uint32_t sum = addition(1, 2);
    printf("%" PRIu32 "\n", sum);
    return 0;
}
