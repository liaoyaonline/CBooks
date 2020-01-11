#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    int Num;
    int NodeLen;
    struct Node *next;
}ListNode;
void ReadNode(int num[]);
void ReadListNode(ListNode* head);
int main()
{
    int num[20]={10,4,5,2,8,9,11,7,23,65,12};
    int tmp = 0;
    int sign = 0;
    scanf("%d",&tmp);
    ReadNode(num);
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    ListNode* TmpNodep = head;
    head->Num = num[0];
    head->NodeLen = 1;
    for(int i = 1;i <= num[0];i++)
    {
        head->next = (ListNode*)malloc(sizeof(ListNode));
        head = head->next;
        head->Num = num[i];
        head->NodeLen = 1;
    }
    head = TmpNodep;
    ReadListNode(head);
    ListNode* p = NULL;
    for(p = head;p != NULL;p = p->next)
    {
        if(tmp == p->Num)
        {
            printf("冒的事情,里面有个个数字 %d\n",p->Num);
            sign = 1;
        }
    }
    printf("\n");
    for(p = head;p->next != NULL;p = p->next)
    {
    }
    if(sign == 0)
    {
        p->next = (ListNode*)malloc(sizeof(ListNode));
        p = p->next;
        p->Num = tmp;
        p->NodeLen = 1;
    }
    ReadListNode(head);
    /*for(int i = 1;i <= num[0];i++)
    {
        if(tmp == num[i])
        {
            printf("冒的事情,里面第　%d 个数字 %d\n",i+1,num[i]);
            sign = 1;
        }
    }
    printf("\n");
    if(sign == 0)
    {
        num[0]++;
        num[num[0]] = tmp;
    }
    ReadNode(num);*/
    return 0;
}
void ReadNode(int num[])
{
    for(int i = 0;i <= num[0];i++)
    {
        printf("%d ",num[i]);
    }
}
void ReadListNode(ListNode* head)
{
    ListNode* p = head;
    for(p = head;p != NULL;p = p->next)
    {
        printf("%d ",p->Num);
    }
}
