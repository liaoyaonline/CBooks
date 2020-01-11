#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char OffsetUrl[80];
void get();
void parse();
int main()
{
    int GetResult = 0;
    FILE *fp;
    fp = fopen("ing.txt","r");
    memset(OffsetUrl,0,sizeof(OffsetUrl));
    fscanf(fp,"%s",OffsetUrl);
    GetResult = GetHahNode(OffsetUrl);
    //get();
    //parse();
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
