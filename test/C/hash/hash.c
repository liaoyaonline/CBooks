#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

char StrTmp[80] = "";

void InitHashmap()
{
    ListNode* HeadTmp = head;
    int m = HASHSIZE;
    memset(StrTmp,0,sizeof(StrTmp));
    for(int i = 0;i < m;i++)
    {
        (head+i)->NodeLen = 0;
        memset((head+i)->Url,0,sizeof((head+i)->Url));
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
        PutHashmap(NodeNum);
        //printf("%s\n\n",StrTmp);
        memset(StrTmp,0,sizeof(StrTmp));//!!!不要删除这个已经做为记录留存
    }
    fclose(fp);
}
void readnode()
{
    ListNode* HeadTmp = head;
    ListNode* ChildNode = head;
    int m = HASHSIZE;
    int error = 0;
    for(int i = 0;i < m;i++)
    {
        if(head->NodeLen != 0)
        {
            if(head->NodeLen >1)
            {
                printf("\n%d\n",head->NodeLen);
                error++;
            }
            ChildNode = head;
            while(ChildNode != NULL)
            {
                printf("阅读第%d个节点的内容为%s  节点长度为%d  地址为 %p,next地址为%p\n",i,ChildNode->Url,ChildNode->NodeLen,ChildNode,ChildNode->next);
                ChildNode = ChildNode->next;
            }
        }
        printf("阅读第%d个节点的内容为%s  标识为%d  地址为 %p,next地址为%p\n",i,head->Url,head->NodeLen,head,head->next);
        head++;
    }
    printf("\n\n总共有这么多个超过１：%d\n",error);
    head = HeadTmp;
}
unsigned int Hash(char *str)
{
    unsigned int seed = 7;
    unsigned int hash = 0;
    int m = HASHSIZE;
    while(*str != '/' && str != NULL)
    {
        str++;
    }
    str++;
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
int PutHashmap(unsigned int HashNum) /*return 1,发现和目标字符串一样。return 0正常结束*/
{
    /*char StrTest[80] = "book/10089";
    if(strcmp(StrTmp,StrTest) == 0)
    {
        printf("就是这个点\n");
    }//测试使用*/
    ListNode* HeadTmp = head;//指针地址
    ListNode* p = NULL;
    int Sign = 0;//用来识别该子链里面是否有节点和StrTmp一样
    head = head + HashNum;
    if(head->NodeLen == 0)//如果hashmap里面没有该字符串
    {
        strcpy(head->Url,StrTmp);//将字符串复制到对应地址的结构体里面
        head->NodeLen = 1;//将节点长度置1
    }
    else//如果hashmap里面有数字
    {
        for(p = head;p != NULL;p = p->next)
        {
            if(strcmp(StrTmp,p->Url) == 0)
            {
                printf("\n\n里面有相同字符串 %s \n",p->Url);
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
            strcpy(p->Url,StrTmp);
            p->NodeLen = 1;
            p->next = NULL;
            head->NodeLen ++;
        }
    }
    head = HeadTmp;
    return 0;
}
int GetHashNode(char *str)
{
    ListNode* HeadTmp = head;
    int SearchResult = 0;
    unsigned int NodeNum = 0;
    NodeNum = Hash(str);
    head = head + NodeNum;
    if(head->NodeLen != 0)
    {
        for(;head != NULL;head = head->next)
        {
            if(strcmp(str,head->Url) == 0)
            {
                //printf("\n查到了，有相同的字符串: %s\n",head->Url);
                SearchResult = 1;
            }
        }
    }
    head = HeadTmp;
    return SearchResult;
}
