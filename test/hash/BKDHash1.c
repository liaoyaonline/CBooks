#include <stdio.h>//将malloc添加进来
#include <stdlib.h>
typedef struct Node
{
    int num;
}ListNode;

unsigned int BKDRHash(char *str);
unsigned int fputhashmap(ListNode* str);
void initHashmap(ListNode* str);//初始化hashMap将所有格子置0
void readHashmap(ListNode* str);//查看hashmap的所有内容
void checkHashmap(ListNode* str);//根据需要输出hashmap的指定内容
int main()
{
    unsigned int result = 0;
    ListNode *head = (ListNode*)malloc(800000*sizeof(ListNode));
    initHashmap(head);
    readHashmap(head);
    fputhashmap(head);
    readHashmap(head);
    checkHashmap(head);
    //char a[40] = "sdfksdfjskf";
    //result = BKDRHash(a);
    //printf("%s \n   %d\n",a,result);
    free(head);
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
unsigned int fputhashmap(ListNode* str)
{
    ListNode* head = str;
    FILE *p;
    char hashtmp[80];
    unsigned int num = 0;
    p=fopen("testhash.txt","r");
    while(!feof(p))
    {
        fscanf(p,"%s",hashtmp);
        num = BKDRHash(hashtmp);
        (head+num)->num++;
        printf("%s  %d      %d\n",hashtmp,num,(head+num)->num);
    }
    fclose(p);
}
void initHashmap(ListNode* str)
{
    ListNode *head = str;
    for(int i = 0;i < 800000;i++)
    {
        head->num = 0;
        head++;
    }
}
void readHashmap(ListNode* str)
{
    ListNode* head = str;
    for(int i = 0;i < 800000;i++)
    {
        printf("%d \n",head->num);
        head++;
    }
}
void checkHashmap(ListNode* str)
{
    ListNode* head = str;
    int badnum = 0;
    int bad[40];
    int j = 0;
    for(int i = 0;i < 800000;i++)
    {
        if(head->num > 1)
        {
            printf("%d  \n",head->num);
            bad[j]=head - str;
            j++;
            badnum++;
        }
        head++;
    }
    printf("%d      %d    \n",bad[0],bad[1]);
    printf("!!!!!!!!!!!!!!!!!!        %d        !!!!!!!!!!!!",badnum);
}
