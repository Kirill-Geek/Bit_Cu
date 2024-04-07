#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint32_t N;
    printf("Введите N: ");
    scanf("%u", &N);

    uint32_t res = N ^ 0xFF000000;
    printf("%u\n", res);

    return 0;
}