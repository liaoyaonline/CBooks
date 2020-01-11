#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
}ListNode;
int testnode(ListNode* str);
void readnode(ListNode* str);
int main()
{
    ListNode *head = (ListNode*)malloc(800000*sizeof(ListNode));
    testnode(head);
    readnode(head);
    return 0;
}
int testnode(ListNode* str)
{
    ListNode* head = str;
    for(int i = 0;i < 800000;i++)
    {
        head->num = i;
        head ++;
    }
    return 0;
}
void readnode(ListNode* str)
{
    ListNode* head = str;
    for(int i = 0;i < 800000;i++)
    {
        printf("%d \n",head->num);
        head++;
    }
}
