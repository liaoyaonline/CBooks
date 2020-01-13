#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
void fCheckUrl();
int main()
{
    int m = HASHSIZE;
    ListNode *p = (ListNode*)malloc(m * sizeof(ListNode));
    head = p;
    InitHashmap();
    fwriteHash();
    readnode();
    fCheckUrl();
    return 0;
}
void fCheckUrl()
{
    int GetResult = 0;
    char UrlTmp[80] = "";
    FILE *fp = fopen("UrlTmp.txt","r");
    FILE *ft = fopen("UrlSame.txt","w");
    FILE *fin = fopen("ing.txt","a");
    while(!feof(fp))
    {
        memset(UrlTmp,0,sizeof(UrlTmp));
        fscanf(fp,"%s",UrlTmp);
        if(feof(fp))
        {
            break;
        }
        GetResult = GetHashNode(UrlTmp);
        if(GetResult == 1)
        {
            printf("\n\n这个是相同的\n");
            printf("%s\n",UrlTmp);
            fprintf(ft,"%s\n",UrlTmp);
            continue;
        }
        printf("\n这个是不同的\n");
        printf("%s\n",UrlTmp);
        fprintf(fin,"%s\n",UrlTmp);
    }
    fclose(fp);
    fclose(ft);
    fclose(fin);
    system("rm UrlTmp.txt");
}
