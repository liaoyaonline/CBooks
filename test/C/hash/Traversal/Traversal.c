#include <stdio.h>
#include <string.h>
void Traversal();
int main()
{
    Traversal();
    return 0;
}
void Traversal()
{
    FILE *fr = fopen("UrlTmp.txt","r");
    FILE *fw = fopen("log.txt","a+");
    char UrlTmp[80];
    while(1)
    {
        memset(UrlTmp,0,sizeof(UrlTmp));
        fscanf(fr,"%s",UrlTmp);
        if(feof(fr))
        {
            break;
        }
        fprintf(fw,"%s\n",UrlTmp);
    }
    fclose(fr);
    fclose(fw);
}
