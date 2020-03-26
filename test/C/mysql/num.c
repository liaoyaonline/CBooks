#include <stdio.h>

int main()
{
    int num = 2003;
    int max = 7;
    int min = 5;
    int cycle = max - min + 1;
    int cyclenum = num - min +1;
    int l = 0;
    int test[10] = {1,2,3,4,5,6,7};
    for(int i = 0;i < cyclenum;i++)
    {
        l = (l + 1) % cycle;
    }
    l = l + min - 2;
    printf("%d\n",test[l]);
    return 0;
}

