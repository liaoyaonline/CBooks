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
struct Node* firsthead=NULL;
int InitHashmap(ListNode* str);
int puthashmap(char* key,ListNode* str);
unsigned int Hash(char *str);
int fwriteHash(ListNode* str);
void readnode(ListNode* str);
int main()
{
    int m = HASHSIZE;
    //char a[40] = "sdfksdfjskf";
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    firsthead = p;
    InitHashmap(firsthead);
    //readnode(p);
    //puthashmap(a,p);
    //readnode(p);
    fwriteHash(firsthead);
    printf("just\n");
    readnode(firsthead);
    free(firsthead);
    return 0;
}
int InitHashmap(ListNode* str)
{
    ListNode* head = str;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        (head+i)->num = 0;
        (head+i)->next = NULL;
        //printf("第 %d 个节点的　num值是　%d\n",i,(head+i)->num);
    }
    return 0;
}
int fwriteHash(ListNode* str)
{
    ListNode* head = str;
    FILE *p;
    char hashtmp[80];
    int i = 0;
    p=fopen("malltest.txt","r");
    while(!feof(p))
    {
        fscanf(p,"%s",hashtmp);
        //printf("第%d次，将字符串　%s 存入hashmap\n",i,hashtmp);
        puthashmap(hashtmp,head);
        i++;
    }
    return 0;
}
/*int testnode(ListNode* str)
{
    ListNode* head = str;
    for(int i = 0;i < 800000;i++)
    {
        head->num = i;
        head ++;
    }
    return 0;
}*/
void readnode(ListNode* str)
{
    ListNode* head = str;
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
int puthashmap(char* key,ListNode* str) /*return 1,发现和目标字符串一样。return 0正常结束*/
{
    ListNode* head = str;//指针地址
    ListNode* headtmp = str;
    //char* tmpKey = key;
    char tmp[80];//字符串
    unsigned int num;//hash后的数值
    //int result = 0;//比较后的结果
    strcpy(tmp,key);//将字符串复制到中间变量
    num = Hash(tmp);
    //printf("路过１号节点\n");
    if((head+num)->num == 0)//如果hashmap里面没有该字符串
    {
        strcpy((head+num)->name,tmp);//将字符串复制到对应地址的结构体里面
        (head+num)->num ++;//将标识位置1
        //printf("hash值是 %d ,字符串是　%s \n",num,(head+num)->name);
    }
    else//如果hashmap里面有数字，但是key不
        //一样，就在该地址进行检索比较
       // ，找到key一样的就停止，找到不一样的就继续往下找，如果结束还没找到，在末尾加入。
    {
        //printf("路过２号节点\n");
        head = head+num;
        //printf("%s    %d\n",head->name,head->num);
        while(head)//不要是空指针
        {
            //printf("\n%d \n",test);
            if(strcmp(tmp,head->name) == 0)
            {
                printf("同一个内容不能写入\n");
                printf("准备写入的字符串:  %s\n",tmp);
                printf("已经有的字符串:    %s\n",head->name);
                return 1;//结束函数
            }
            //printf("第３号节点\n");
            headtmp = head;
            head = head->next;
        }
        ListNode *q = (ListNode*)malloc(sizeof(ListNode));
        head = headtmp;
        printf("节点的内容为%s  标识为%d  当前地址为%p,next地址为 %p\n",head->name,head->num,head,head->next);
        head->next = q;
        printf("节点的内容为%s  标识为%d  当前地址为 %p,next地址为　%p\n",head->name,head->num,head,head->next);
        //head->next = (ListNode*)malloc(sizeof(ListNode));
        //printf("第4号节点\n");
        //head = head->next;
        strcpy(head->name,tmp);
        //printf("没有发现相同的字符串，已经将字符串写入该链表，字符串为: %s",tmp);
        head->num = 1;
    }
    return 0;
}
