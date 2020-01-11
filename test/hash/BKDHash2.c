#include <stdio.h>//对结构进行梳理
#include <stdlib.h>
#define HASHSIZE 8
typedef struct Node//节点，name用来存储key，遭遇hash冲突时用于校准，num用于标识有和无，next指向hash冲突的下一个指针
{
    char name[80];
    int num;
    struct Node *next;
}ListNode;
int puthashmap(int key,ListNode* str);
int gethashmap(int key,ListNode* str);
int InitHashmap(ListNode* str);
void readnode(ListNode* str);
//unsigned int BKDRHash(char *str);
//unsigned int fputhashmap(ListNode* str);
//void initHashmap(ListNode* str);//初始化hashMap将所有格子置0
//void readHashmap(ListNode* str);//查看hashmap的所有内容
//void checkHashmap(ListNode* str);//根据需要输出hashmap的指定内容
int main()
{
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    InitHashmap(p);
    readnode(p);
    free(p);
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
int InitHashmap(ListNode* str)
{
    ListNode* head = str;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {   
        (head+i)->num = 0;
    }
    return 0;
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
void readnode(ListNode* str)
{
    ListNode* head = str;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        printf("%d \n",head->num);
        head++;
    }
}
