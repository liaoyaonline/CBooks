#include <stdio.h>
unsigned int BKDRHash(char *str);
unsigned int fwrite_hashmap();
int main()
{
    unsigned int result = 0;
    //char a[40] = "sdfksdfjskf";
    //result = BKDRHash(a);
    //printf("%s \n   %d\n",a,result);
    fwrite_hashmap();
    return 0;
}
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 31;
    unsigned int hash = 0;
    while(*str != '/' && str != NULL)
    {
        str++;
    }
    while (*str)
    {
        hash = hash * seed + (*str++);
        //printf("%c %d..   %d  \n",*str,*str,hash);
    }
    hash = hash & 0x7FFFFFFF;
    hash = hash % 800000;

    return hash;
}
unsigned int fwrite_hashmap()
{
    FILE *p;
    char hashtmp[80];
    unsigned int num = 0;
    p=fopen("testhash.txt","r");
    while(!feof(p))
    {
        fscanf(p,"%s",hashtmp);
        num = BKDRHash(hashtmp);
        printf("%s  %d  \n",hashtmp,num);
    }
    fclose(p);
}
