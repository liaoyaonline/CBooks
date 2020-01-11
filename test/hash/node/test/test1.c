#include <stdio.h>
#include <string.h>
int main()
{
    char StrTmp[80];
    memset(StrTmp,0,sizeof(StrTmp));
    FILE *fp;
    fp=fopen("test.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",StrTmp);
        if(feof(fp))
        {
            break;
        }
        printf("%s\n\n",StrTmp);
    }
    fclose(fp);
    return 0;
}

