#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HASHSIZE 8
typedef struct Node
{
    char name[80];
    struct Node *next;
}ListNode;
void readnode(ListNode* str);
void test(ListNode* str);
int main()
{
    int m = HASHSIZE;
    ListNode* q = (ListNode*)malloc(m*sizeof(ListNode));
	test(q);
    readnode(q);
	return 0;
}
void readnode(ListNode* str)
{
    ListNode* head = str;
    ListNode* childNode = str;
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
        printf("阅读节点的内容为%s地址为 %p,next地址为%p\n",head->name,head,head->next);
        head++;
    }
}
void test(ListNode* str)
{
    char tmp[80] = "jokerjoker";
    ListNode* head = str;
    head = head+2;
    //head->next = NULL;
    //head = head->next;
    ListNode *q = (ListNode*)malloc(sizeof(ListNode));
    head->next = q;
    printf("test阅读节点的内容为%s地址为 %p,next地址为%p\n",head->name,head,head->next);
    head = q;
    strcpy(head->name,tmp);
    head->next = NULL;
}
