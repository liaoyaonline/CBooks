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
        printf("阅读第%d个节点的内容为%s  地址为 %p\n",i,head->name,head->next);
        head++;
    }
}
void test(ListNode* str)
{
    ListNode* head = str;
    head = head+2;
    char tmp[80] = "jokerjoker";
    strcpy(head->name,tmp);
    printf("%s\n",head->name);
    ListNode* q = (ListNode*)malloc(sizeof(ListNode));
    head->next = q;
    head = head->next;
    head->next = NULL;
    strcpy(head->name,tmp);
    printf("%s\n",head->name);
}
