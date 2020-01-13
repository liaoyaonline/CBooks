#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED
#define HASHSIZE 80000
typedef struct Node
{
    char Url[80];
    int NodeLen;
    struct Node *next;
}ListNode;
ListNode *head;
extern char StrTmp[80];
void InitHashmap();
int PutHashmap(unsigned int HashNum);
unsigned int Hash(char *str);
void fwriteHash();
void readnode();
int GetHashNode(char *str);
void fCheckUrl();

#endif
