#include <stdio.h>
#include <stdlib.h>
int main()
{
    int* a=(int*)malloc(200000*sizeof(int));
    for(int i = 0;i < 200000;i++)
    {
        a[i] = 0;
    }
    for(int j = 0;j < 200000;j++)
    {
        printf("%d\n",a[j]);
    }
    free(a);
    return 0;
}

