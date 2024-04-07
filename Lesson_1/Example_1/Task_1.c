#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    int32_t N;
    printf("Введите N: ");
    scanf("%d", &N);
    int max;
    int n = 0;
    int32_t count = 1;
    int32_t num = 0;
    bool flag = true;
    printf("Введите %d чисел: ", N);
    while(scanf("%d", &num) == 1)
    {
        if(max == num)
        {
            count++;
        }
        if(num > max)
        {
            max = num;
            count = 1;
        }
        if(flag)
        {
            max = num;
            flag = false;
        }
        n++;
        if(n == N)
        {
            break; 
        }
    }
    printf("Максимальное число втречается : %d\n", count);


    return 0;
}