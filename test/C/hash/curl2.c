#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

char OffsetUrl[80];
void get();
void parse();
int main()
{
    int GetResult = 0;
    FILE *fp;
    fp = fopen("ing.txt","r");
    memset(OffsetUrl,0,sizeof(OffsetUrl));
    fscanf(fp,"%s",OffsetUrl);
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    fwriteHash();
    GetResult = GetHashNode(OffsetUrl);
    printf("测试结果是　%d\n",GetResult);
    //get();
    //parse();
    free(head);
    return 0; 
}
void get(void)
{
    system("bash get.sh");
}
void parse()
{
    system("bash parse.sh");
}
