#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

char OffsetUrl[80];
void get();
void parse();
int main()
{
    int GetResult = 0;
    unsigned int NodeNum = 0;
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    fwriteHash();
    while(1)
    {
        FILE *fp = fopen("ing.txt","r");
        memset(OffsetUrl,0,sizeof(OffsetUrl));
        fscanf(fp,"%s",OffsetUrl);
        if(feof(fp))
        {
            break;
        }
        GetResult = GetHashNode(OffsetUrl);
        if(GetResult == 1)
        {
            printf("\n\n这个是相同的\n");
            printf("%s\n",OffsetUrl);
            system("sed -i '1d' ing.txt");
            fclose(fp);
            continue;
        }
        system("sed -i '1d' ing.txt");
        NodeNum = Hash(OffsetUrl);
        //get();
        //parse();
        PutHashmap(NodeNum);
        fclose(fp);
    }
    GetResult = GetHashNode(OffsetUrl);
    printf("测试结果是　%d\n",GetResult);
    //get();
    //parse();
    free(head);
    return 0; 
}
void get(void)
{
    system("bash get.sh");
}
void parse()
{
    system("bash parse.sh");
}
