#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    scanf("%d,%d",&a,&b);
    if(a == 0)
        printf("执行A空\n");
    else
        printf("执行A不空\n");
    if(b == 0)
        printf("执行B空\n");
    else
        printf("执行B不空\n");
    return 0;
}

