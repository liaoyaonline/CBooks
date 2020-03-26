#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "hash.h"

char OffsetUrl[80];
void get();
void parse();
int main()
{
    int TimeSize = 0;
    int SleepTime = 0;
    int GetResult = 0;
    unsigned int NodeNum = 0;
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    fwriteHash();
    readnode();
    while(TimeSize < 10)
    {
        TimeSize++;
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
        srand((unsigned)time(NULL));
        SleepTime = (rand() % 50 +1);
        printf("休眠 %d s\n",SleepTime);
        printf("休眠 %d s\n",SleepTime);
        sleep(SleepTime);
        system("sed -i '1d' ing.txt");
        printf("%s\n",OffsetUrl);
        get();
        parse();
        NodeNum = Hash(OffsetUrl);
        PutHashmap(NodeNum);
        printf("OffsetUrl: %s NodeNum:%d\n",OffsetUrl,NodeNum);
        fclose(fp);
    }
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
