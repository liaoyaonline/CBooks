#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 80
typedef struct Node//节点，name用来存储key，遭遇hash冲突时用于校准，num用于标识有和无，next指向hash冲突的下一个指>
{
    char name[80];
    int num;
    struct Node *next;
}ListNode;
ListNode *head = NULL;
int InitHashmap();
int puthashmap();
unsigned int Hash(char *str);
int fwriteHash();
void readnode();
void testnode();
void test2();
int main()
{
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    printf("1\n");
    fwriteHash();
    //puthashmap();
    printf("2\n");
    readnode();
    //test2();
    //readnode();
    printf("3\n");
    free(head);
    return 0;
}
void testnode()
{
    ListNode *tmphead = head;
    printf("阅读testNode开始节点标识为%d 地址为 %p,next地址为%p\n",head->num,head,head->next);
    for(int i = 0;i < 6;i++)
    {
        ListNode *q = (ListNode*)malloc(sizeof(ListNode));
        head->num = i;
        head->next = q;
        head = head + 1;
        printf("阅读testNode开始节点标识为%d 地址为 %p,next地址为%p\n",head->num,head,head->next);
    }
    printf("~~~~~~~~~~\n\n");
    head = tmphead;
}
void test2()
{
    testnode();
}
int InitHashmap()
{
    ListNode* tmphead = head;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        (head+i)->num = 0;
        (head+i)->next = NULL;
    }
    head = tmphead;
    return 0;
}
int fwriteHash()
{
    ListNode* tmphead = head;
    FILE *p;
    char hashtmp[80];
    unsigned int numnode = 0;
    p=fopen("malltest.txt","r");
    while(!feof(p))
    {
        fscanf(p,"%s",hashtmp);
        numnode = Hash(hashtmp);
        head = head + numnode;
        puthashmap();
        head = tmphead;
    }
    head = tmphead;
    return 0;
}
void readnode()
{
    ListNode* tmphead = head;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        printf("阅读第%d个节点　标识为%d  地址为 %p,next地址为%p\n",i,head->num,head,head->next);
        head++;
    }
    head = tmphead;
}
unsigned int Hash(char *str)
{
    unsigned int seed = 31;
    unsigned int hash = 0;
    int m = HASHSIZE;
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
    hash = hash % m;
    //printf("输出hash值: %d\n",hash);

    return hash;
}
int puthashmap() /*return 1,发现和目标字符串一样。return 0正常结束*/
{
    ListNode* tmphead = head;//指针地址
    if(head->num != 0)//如果hashmap里面没有该字符串
    {
        head->num ++;//将标识位置1
    }
    else//如果hashmap里面有数字，但是key不
    {
        ListNode *q = (ListNode*)malloc(sizeof(ListNode));
        printf("节点的内容为%s  标识为%d  当前地址为%p,next地址为 %p\n",head->name,head->num,head,head->next);
        head->next = q;
        printf("节点的内容为%s  标识为%d  当前地址为 %p,next地址为　%p\n",head->name,head->num,head,head->next);
        head->num = 1;
        //head -> next = NULL;
    }
    head = tmphead;
    return 0;
}
