#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
    int a;
    struct Node* next;
};
struct Node* head = NULL;
struct Node* end = NULL;
void AddListTill(int a);
void ScanList();
struct Node* FindNode(int a);
void FreeList();
void AddListRand(int index,int a);
void DeleteListTail();
void DeleteListHead();
void DeleteListRand(int a);
int main()
{
    struct Node *pFind;
    for(int i = 0;i < 6;i++)
    {
        AddListTill(i);
    }
    DeleteListRand(4);
    ScanList();
    FreeList();
    return 0;
}
void AddListTill(int a)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->a = a;
    temp->next=NULL;
}
