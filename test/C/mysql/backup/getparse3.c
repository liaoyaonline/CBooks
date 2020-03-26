#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>
#include "mysqlplus.h"
BlInfo BooklistInfo;
BInfo BookInfo;
char BookId[1000][80];
int i;
static size_t curlCallBackFileWrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(buffer, size, nmemb , (FILE *)stream);
    return written;
}
int getinfo(char* booklistid,char* url);
int regexblfile(char* booklistid,const char* pattern,char flag);
int readBLInfo(int booknum);
int BooklistParsing(char* BooklistId);
int main()
{
    char* url = "5a405904da8315b47e51cbb6";
    BooklistParsing(url);
    return 0;
}
int getinfo(char* booklistid,char* url)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    FILE* fp;
    fp = fopen(booklistid,"wb");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallBackFileWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    fclose(fp);

    if(CURLE_OK == res) {
      char *ct;
      /* ask for the content-type */
      res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

      if((CURLE_OK == res) && ct)
        printf("We received Content-Type: %s\n", ct);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
int regexblfile(char* booklistid,const char* pattern,char flag)
{
    int n,len,count;
    int t;
    char BooklistValue[3][20];
    char BookType[40][40];
    int value = 0;
    int booktype = 0;
    char buffer[512];
    regmatch_t pmatch[2];
    const size_t nmatch = 2;
    regex_t reg;
    char str[1024*1024];
    char *p = NULL;
    //书号const char * pattern = "href=\"\\s*/\(book/[0-9]{1,6}\)\\s*";
    //name const char * pattern = "class=\"booklistName\"[^>]*.\([^<]*)\\s*";
    //作者 const char * pattern = "userName\":\"\([^\"]*)\"},\"title\"";
    //浏览，书本数目，收藏123..const char * pattern = "class=\"number-border-itemvalue\"[^>]*.\([^<]*)";
    //更新时间const char * pattern = "class=\"BooklistUpdateAtInfo\"[^>]*.\([^<]*)";
    //书籍类型const char * pattern = "href=\"/bookstore/\\\?classId=[^>]*.\([^<]*)";
    //书单简介const char * pattern = "BooklistInfoIntro\"[^>]*.[^>]*.[^>]*.\([^<]*)";
    memset(str,0,sizeof(str));
    n = 0;
    count = 0;
    int fd = open(booklistid,O_RDONLY);
    if(fd < 0)
    {
        printf("file: %s open error\n",booklistid);
        return -1;
    }
    while ((n = read(fd, str+count,1024)) != 0){
        if (n == -1)
        {
            printf("file read error\n");
            return -1;
        }
        count += n;
    }
    close(fd);
    printf("\nfile read over! begn URL analyse now...\n");

    p = str;

    if((t = regcomp(&reg,pattern,REG_EXTENDED)) != 0)
    {
        regerror(t, &reg, buffer, sizeof buffer);
        fprintf(stderr,"grep: %s (%s)\n",buffer,pattern);
        return -1;
    }
    fprintf(stderr,"grep: %s (%s)\n",buffer,pattern);
    while(regexec(&reg,p,nmatch,pmatch,0) != REG_NOMATCH)
    {
        len = (pmatch[1].rm_eo - pmatch[1].rm_so);
        p = p + pmatch[1].rm_so;
        char *tmp = (char *)calloc(len+1,1);
        strncpy(tmp,p,len);
        tmp[len] = '\0';
        switch(flag)
        {
        case '1' :
            printf("读取书单内书号\n" );
            strncpy(BookId[i],tmp,len+1);
            i++;
            break;
        case '2' :
            printf("读取书单名称\n");
            strncpy(BooklistInfo.BooklistName,tmp,len+1);
            break;
        case '3' :
            printf("读取书单作者\n" );
            strncpy(BooklistInfo.BooklistAuthor,tmp,len+1);
            break;
        case '4' :
            printf("读取书单基本信息\n" );
            strncpy(BooklistValue[value],tmp,len+1);
            value++;
            break;
        case '5' :
            printf("读取书单类型\n" );
            strncpy(BookType[booktype],tmp,len+1);
            booktype++;
            break;
        case '6':
            printf("读取书单介绍\n");
            strncpy(BooklistInfo.BooklistIntro,tmp,len+1);
            break;
        case '7':
            printf("读取书单更新时间\n");
            strncpy(BooklistInfo.BooklistUpdata,tmp,len+1);
            break;
        default :
            printf("无效的flag,不能读取\n" );
        }
        p = p + len + (pmatch[0].rm_eo - pmatch[1].rm_eo);
        printf("%s\n",tmp);
    }
    if(flag == '4')
    {
        strcpy(BooklistInfo.BooklistViews,BooklistValue[0]);
        strcpy(BooklistInfo.BooklistCount,BooklistValue[1]);
        strcpy(BooklistInfo.BooklistKeep,BooklistValue[2]);
    }
    if(flag == '5')
    {
        BooklistInfo.BookTypeNum = booktype;
        for(int i = 0;i < booktype;i++)
        {
            strcat(BooklistInfo.BookType,BookType[i]);
        }
    }
    return 0;
}
int readBLInfo(int booknum)
{
    for(int i = 0; i < booknum;i++)
    {
        printf("%s\n",BookId[i]);
    }
    printf("%s\n",BooklistInfo.BooklistName);
    printf("%s\n",BooklistInfo.BooklistAuthor);
    printf("%s   ",BooklistInfo.BooklistViews);
    printf("%s   ",BooklistInfo.BooklistCount);
    printf("%s   \n",BooklistInfo.BooklistKeep);
    printf("%s    \n",BooklistInfo.BookType);
    printf("%s\n",BooklistInfo.BooklistUpdata);
    printf("%s\n",BooklistInfo.BooklistIntro);
    return 0;
}
int BooklistParsing(char* BooklistId)
{
    if(strlen(BooklistId) < 7)
    {
        printf("in booklistId is error! %ld\n",strlen(BooklistId));
        return -1;
    }
    BlInfo *pblist = &BooklistInfo;
    BInfo *pbook = &BookInfo;
    i = 0;
    int pagenum = 0;
    int Inquire = 0;
    char Attribute[3][40];
    strcpy(Attribute[0],"BookId");
    strcpy(Attribute[1],"BooklistId");
    strcpy(Attribute[2],"BooksId");
    char TargetTable[3][100];
    strcpy(TargetTable[0],"BookDone");
    strcpy(TargetTable[1],"BooklistDone");
    strcpy(TargetTable[2],"ing");
    char flag = '1';
    int booknum = 0;
    char booklisturl[400];
    char booksurl[400];
    char booklistid[40];
    char booksid[100];
    char frontblurl[200] = "https://www.yousuu.com/booklist/";
    char urlpage[20] = "?page=";
    char page = '2';
    char pageurl[200];
    const char * pattern[10];
    memset(pageurl,0,sizeof(pageurl));
    pattern [1] = "href=\"\\s*/book/\([0-9]{1,6})\\s*";
    pattern [2] = "class=\"booklistName\"[^>]*.\([^<]*)\\s*";
    pattern [3] = "userName\":\"\([^\"]*)\"},\"title\"";
    pattern [4] = "class=\"number-border-itemvalue\"[^>]*.\([^<]*)";
    pattern [5] = "href=\"/bookstore/\\\?classId=[^>]*.\([^<]*)";
    pattern [6] = "BooklistInfoIntro\"[^>]*.[^>]*.[^>]*.\([^<]*)";
    pattern [7] = "class=\"BooklistUpdateAtInfo\"[^>]*.\([^<]*)";
    //getinfo(booklistid,url);
    strcpy(booklistid,BooklistId);
    printf("booklistid :%s\n",booklistid);
    Inquire = MysqlInquire(booklistid,TargetTable[2],Attribute[2]);
    if(Inquire > 0)
    {
        MysqlDelete(booklistid,TargetTable[2],Attribute[2]);
        printf("delete id: %s\n",booklistid);
    }
    else
    {
        printf("id error ,not found from ing :%s\n",booklistid);
        return -2;
    }
    strcpy(BooklistInfo.BooklistId,booklistid);//将ｉｄ信息写入结构体
    sprintf(booklisturl,"%s%s",frontblurl,booklistid);//建立对应的ｕｒｌ
    printf("URL:%s\n",booklisturl);
    getinfo(booklistid,booklisturl);
    for(int i = 1;i < 8;i++)
    {
        regexblfile(booklistid,pattern[i],flag);
        flag++;
    }
    readBLInfo(i);
    Inquire = MysqlInquire(booklistid,TargetTable[1],Attribute[1]);
    if(Inquire == 0)
        MysqlUpload(pblist,pbook,BookId[0],TargetTable[1],'2');//将爬取到的书本信息上传
    booknum = BooklistInfo.BooklistCount[0] - '0';
    printf("%d\n",booknum);
    for(int i = 1;i < (int)strlen(BooklistInfo.BooklistCount);i++)
    {
        booknum = (booknum * 10) + (BooklistInfo.BooklistCount[i] - '0');
        i++;
    }
    printf("%d\n  %s  %d\n",booknum,BooklistInfo.BooklistCount,(int)strlen(BooklistInfo.BooklistCount));
    if(booknum > 0)
    {
        pagenum = booknum / 20;
        if(booknum % 20 != 0)
            pagenum++;
    }
    printf("%d\n",pagenum);
    if(pagenum > 0)
    {
        for(int i = 2, flag = '1';i <= pagenum;i++)
        {
            sprintf(booksurl,"%s%s%s%c",frontblurl,booklistid,urlpage,page);//建立对应的书本sfilename
            sprintf(booksid,"%sbooks%c",booklistid,page);//建立对应的书本sfilename
            printf("booksId:%s\nbooksURL: %s\n",booksid,booksurl);
            getinfo(booksid,booksurl);
            regexblfile(booksid,pattern[1],flag);
            page++;
        }
    }
    readBLInfo(i);
    for(int i = 0;i < booknum;i++)//将爬取到的书单ｉｄ，将不在ing里面的ｉｄ上传到ing里面
    {
        Inquire = MysqlInquire(BookId[i],TargetTable[2],Attribute[2]);
        if(Inquire == 0)
            MysqlUpload(pblist,pbook,BookId[i],TargetTable[2],'3');
    }
    return 0;
}
