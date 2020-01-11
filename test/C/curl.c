#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char FilePathTmp[80] = "/home/liaoya/github/CBooks/test/result/";
char UrlPathTmp[80] = "www.yousuu.com/";
char OffsetUrl[80];
char FileNameTmp[80];
char FileName[80];
char FilePath[80];
char UrlPath[80];
void get(void);
int main()
{
    printf("ready go!!!!");
    get();
    return 0;
}
void get(void)
{
    FILE *fp;
    char *FileExtp = ".txt";
    fp = fopen("ing.txt","r");
    char *p = OffsetUrl;
    char *fnamep = FileNameTmp;
    memset(OffsetUrl,0,sizeof(OffsetUrl));
    memset(FileNameTmp,0,sizeof(FileNameTmp));
    memset(FileName,0,sizeof(FileName));
    fscanf(fp,"%s",OffsetUrl);//将第一行复制到OffsetUrl
    printf("\nOffsetUrl: %s FileNameTmp: %s FileName: %s\n",OffsetUrl,FileNameTmp,FileName);
    while(*p != '/' && p != NULL)
    {
        p++;
    }
    printf("%c\n",*p);
    p++;
    strcpy(FileNameTmp,p);
    /*while(p != NULL)//将'/'之后的字符复制到FileNameTmp
    {
        *fnamep = *p;
        p++;
        fnamep++;
    }*/
    printf("\nOffsetUrl: %s FileNameTmp: %s FileName: %s\n",OffsetUrl,FileNameTmp,FileName);
    strcpy(FileName,FileNameTmp);//将FileNameTmp复制给FileName并添加.txt
    strcat(FileName,FileExtp);
    printf("\nOffsetUrl: %s FileNameTmp: %s FileName: %s\n",OffsetUrl,FileNameTmp,FileName);
    strcpy(FilePath,FilePathTmp);
    printf("\nFilePath: %s  FilePathTmp: %s FileName: %s UrlPath: %s  UrlPathTmp : %s OffsetUrl: %s\n",FilePath,FilePathTmp,FileName,UrlPath,UrlPathTmp,OffsetUrl);
    strcat(FilePath,FileName);
    printf("\nFilePath: %s  FilePathTmp: %s FileName: %s UrlPath: %s  UrlPathTmp : %s OffsetUrl: %s\n",FilePath,FilePathTmp,FileName,UrlPath,UrlPathTmp,OffsetUrl);
    strcpy(UrlPath,UrlPathTmp);
    printf("\nFilePath: %s  FilePathTmp: %s FileName: %s UrlPath: %s  UrlPathTmp : %s OffsetUrl: %s\n",FilePath,FilePathTmp,FileName,UrlPath,UrlPathTmp,OffsetUrl);
    strcat(UrlPath,OffsetUrl);
    printf("\nFilePath: %s  FilePathTmp: %s FileName: %s UrlPath: %s  UrlPathTmp : %s OffsetUrl: %s\n",FilePath,FilePathTmp,FileName,UrlPath,UrlPathTmp,OffsetUrl);
    fclose(fp);
    system("sed -i '1d' ing.txt");
    system("curl -L %s > %s",UrlPath,FileName);
}
