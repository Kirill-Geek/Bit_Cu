#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int find_odd(uint32_t arr[], size_t n)
{
    uint32_t res = 0;
    for(size_t i = 0; i<n ; i++)
    {
        res^=arr[i];
    }
    return res;
}

int main(void)
{
    int32_t N;
    printf("Введите N: ");
    scanf("%d", &N);
    uint32_t arr[N];
    printf("Введите %d чисел: ", N);
    for(int i =0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    size_t n = sizeof(arr)/sizeof(arr[0]);
    printf("Искомый элемент = %"PRId32"\n", find_odd(arr,n));

    return 0;
}