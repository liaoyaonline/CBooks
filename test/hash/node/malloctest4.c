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
void InitHashmap();
int puthashmap(unsigned int HashNum);
unsigned int Hash(char *str);
void fwriteHash();
void readnode();
int main()
{
    int m = HASHSIZE;
    //char a[40] = "sdfksdfjskf";
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    readnode(p);
    //puthashmap(a,p);
    //readnode(p);
    fwriteHash();
    printf("just\n");
    readnode();
    free(head);
    return 0;
}
void InitHashmap()
{
    ListNode* HeadTmp = head;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        (head+i)->num = 0;
        (head+i)->next = NULL;
        //printf("第 %d 个节点的　num值是　%d\n",i,(head+i)->num);
    }
    head = HeadTmp;
}
void fwriteHash()
{
    ListNode* HeadTmp = head;
    FILE *p;
    char HashTmp[80];
    unsigned int NodeNum = 0;
    int i = 0;
    p=fopen("malltest.txt","r");
    while(!feof(p))
    {
        fscanf(p,"%s",HashTmp);
        NodeNum = Hash(HashTmp);
        puthashmap(NodeNum);
        i++;
    }
    head = HeadTmp;
}
void readnode()
{
    ListNode* HeadTmp = head;
    //ListNode* childNode = str;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        /*if(head->num != 0)
        {
            childNode = head;
            while(childNode != NULL)
            {
                printf("这是第 %d 个节点的子节点啦啦啦,节点内容为%s 标识为 %d \n",i,childNode->name,childNode->num);
                childNode = childNode->next;
            }
        }*/
        printf("阅读第%d个节点的内容为%s  标识为%d  地址为 %p,next地址为%p\n",i,head->name,head->num,head,head->next);
        head++;
    }
    head = HeadTmp;
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
int puthashmap(unsigned int HashNum) /*return 1,发现和目标字符串一样。return 0正常结束*/
{
    ListNode* HeadTmp = head;//指针地址
    head = head + HashNum;
    //printf("路过１号节点\n");
    if(head->num == 0)//如果hashmap里面没有该字符串
    {
        //strcpy((head+num)->name,tmp);//将字符串复制到对应地址的结构体里面
        head->num ++;//将标识位置1
        //printf("hash值是 %d ,字符串是　%s \n",num,(head+num)->name);
    }
    else//如果hashmap里面有数字，但是key不
    {
        ListNode *q = (ListNode*)malloc(sizeof(ListNode));
        head->next = q;
        head->num = 1;
    }
    head = HeadTmp;
    return 0;
}
