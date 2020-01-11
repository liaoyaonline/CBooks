#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 80
typedef struct Node//节点，name用来存储key，遭遇hash冲突时用于校准，num用于标识有和无，next指向hash冲突的下一个指>
{
    char name[80];
    int NodeLen;
    struct Node *next;
}ListNode;
ListNode *head = NULL;
char StrTmp[80] = "";
void InitHashmap();
int puthashmap(unsigned int HashNum);
unsigned int Hash(char *str);
void fwriteHash();
void readnode();
int main()
{
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    //readnode(p);
    //puthashmap(a,p);
    //readnode(p);
    fwriteHash();
    //printf("just\n");
    //readnode();
    free(head);
    return 0;
}
void InitHashmap()
{
    ListNode* HeadTmp = head;
    int m = HASHSIZE;
    memset(StrTmp,0,sizeof(StrTmp));
    for(int i = 0;i < m;i++)
    {
        (head+i)->NodeLen = 0;
        memset((head+i)->name,0,sizeof((head+i)->name));
        (head+i)->next = NULL;
    }
    head = HeadTmp;
}
void fwriteHash()
{
    FILE *fp;
    unsigned int NodeNum = 0;
    fp=fopen("malltest.txt","r");
    while(!feof(fp))
    {
        memset(StrTmp,0,sizeof(StrTmp));
        fscanf(fp,"%s",StrTmp);
        if(feof(fp))
        {
            break;
        }
        NodeNum = Hash(StrTmp);
        puthashmap(NodeNum);
        printf("%s\n\n",StrTmp);
        memset(StrTmp,0,sizeof(StrTmp));//!!!不要删除这个已经做为记录留存
    }
    fclose(fp);
}
void readnode()
{
    ListNode* HeadTmp = head;
    ListNode* ChildNode = head;
    int m = HASHSIZE;
    for(int i = 0;i < m;i++)
    {
        if(head->NodeLen != 0)
        {
            ChildNode = head;
            while(ChildNode != NULL)
            {
                printf("阅读第%d个节点的内容为%s  标识为%d  地址为 %p,next地址为%p\n",i,ChildNode->name,ChildNode->NodeLen,ChildNode,ChildNode->next);
                ChildNode = ChildNode->next;
            }
        }
        printf("阅读第%d个节点的内容为%s  标识为%d  地址为 %p,next地址为%p\n",i,head->name,head->NodeLen,head,head->next);
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
    ListNode* p = NULL;
    int Sign = 0;//用来识别该子链里面是否有节点和StrTmp一样
    head = head + HashNum;
    if(head->NodeLen == 0)//如果hashmap里面没有该字符串
    {
        strcpy(head->name,StrTmp);//将字符串复制到对应地址的结构体里面
        head->NodeLen = 1;//将节点长度置1
    }
    else//如果hashmap里面有数字
    {
        for(p = head;p != NULL;p = p->next)
        {
            if(strcmp(StrTmp,head->name) == 0)
            {
                printf("\n\n里面有相同字符串 %s \n",p->name);
                Sign = 1;
            }
        }//将p回到子链的末尾节点
        for(p = head;p->next != NULL; p = p->next)//如果出现问题，改为head操作
        {
        }
        if(Sign == 0)//如果没有和StrTmp一样的字符串，在子链末尾添加节点
        {
            p->next = (ListNode*)malloc(sizeof(ListNode));
            p = p->next;
            strcpy(head->name,StrTmp);
            p->NodeLen = 1;
            head->NodeLen ++;
        }
    }
    head = HeadTmp;
    return 0;
}
