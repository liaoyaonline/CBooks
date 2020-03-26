#include <stdio.h>

int main()
{
    float x1;
    float x2;
    float x3;
    float x4;
    float x5;
    int pnum;
    float pnumb;
    float scoreA;
    float scoreB;
    scanf("%f,%f,%f,%f,%f,%d",&x1,&x2,&x3,&x4,&x5,&pnum);
    pnumb = pnum - (x1*pnum);
    scoreA = ((x1*pnum*2)+(x2*pnum*4)+(x3*pnum*6)+(x4*pnum*8)+(x5*pnum*10)) / pnum;
    scoreB = ((x2*pnum*4)+(x3*pnum*6)+(x4*pnum*8)+(x5*pnum*10)) / pnumb;
    printf("SCoreA :%f     SCoreB:%f\n",scoreA,scoreB);
    return 0;
}

