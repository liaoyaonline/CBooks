#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char OffsetUrl[80];
int main()
{
    char test[80] = "book/172672";
    while(1)
    {
        FILE *fp = fopen("ing.txt","r");
        memset(OffsetUrl,0,sizeof(OffsetUrl));
        fscanf(fp,"%s",OffsetUrl);
        if(feof(fp))
        {
            break;
        }
        if(strcmp(test,OffsetUrl) == 0)
        {
            printf("\n\n这个是相同的\n");
            printf("%s\n",OffsetUrl);
            system("sed -i '1d' ing.txt");
            fclose(fp);
            continue;
        }
        printf("%s\n",OffsetUrl);
        system("sed -i '1d' ing.txt");
        fclose(fp);
    }
    return 0;
}

