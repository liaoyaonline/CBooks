# 关于一些问题
## 在函数内给结构体数组添加横向链表节点。
代码如下图所示
```cpp
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
    char tmp[80] = "jokerjoker";
    ListNode* head = str;
    head = head+2;
    //head->next = NULL;
    //head = head->next;
    ListNode *q = (ListNode*)malloc(sizeof(ListNode));
    head->next = q;
    head = q;
    strcpy(head->name,tmp);
    head->next = NULL;
}
```
这样能发现第二个结构体发生改变，其next多了一个节点
但是如果将test函数改变为如下
```
void test(ListNode* str)
{
    char tmp[80] = "jokerjoker";
    ListNode* head = str;
    head = head+2;
    //head->next = NULL;
    head = head->next;
    ListNode *q = (ListNode*)malloc(sizeof(ListNode));
    //head->next = q;
    head = q;
    strcpy(head->name,tmp);
    head->next = NULL;
}

```
仅仅是变换了一下位置，发现第二个结构体的next后面没有发生改变
这是为什么，为什么换一下位置能够让该结构体保存的地址发生变换。
按照我之前所学的，指针是能够改变指向地址里面的内容，如果能够
改变地址，岂不是违背了这个理念。如果不能改变那之前的各种链表
增删改操作不也是这么来的吗？
