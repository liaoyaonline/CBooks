#include <stdio.h>

int main()
{
    int n;
    int tmp=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        tmp+=i;
    }
    float a;
    float b;
    a = 43.0 / 100.0;
    b = 425.0 / 700.0;
    printf("%lf    %lf",a,b);
    printf("%d,%d\n",n,tmp);
    tmp = tmp / n;
    printf("%d",tmp);
    return 0;
}

