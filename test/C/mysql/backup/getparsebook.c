#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>
typedef struct Books
{
    char BookId[100];
    char BookName[100];
    char BookAuthor[100];
    char BookWordCount[100];
    char BookUpdata[100];
    char BookScore[100];
    char BookScoreCount[100];
    char OneStarRate[20];
    char TwoStarRate[20];
    char ThreeStarRate[20];
    char FourStarRate[20];
    char FiveStarRate[20];
    char BookClass[400];
    char AddListCount[20];
    char BookIntro[1000];
} BInfo;
BInfo BookInfo;
char BookId[200][80];
int i;
static size_t curlCallBackFileWrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(buffer, size, nmemb , (FILE *)stream);
    return written;
}
int getinfo(char* booklistid,char* url);
int regex(char* booklistid,const char* pattern,char flag);
int readBLInfo(int booknum);
int BooklistParsing(char* BooklistId);
int main()
{
    char* url = "https://www.yousuu.com/booklist/5a405904da8315b47e51cbb6";
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
int regex(char* booklistid,const char* pattern,char flag)
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
    //name const char * pattern = "class=\"BookName\"[^>]*.\([^<]*)\\s*";
    //作者 const char * pattern = "userName\":\"\([^\"]*)\"},\"title\"";
    //浏览，书本数目，收藏123..const char * pattern = "class=\"number-border-itemvalue\"[^>]*.\([^<]*)";
    //更新时间const char * pattern = "class=\"BooklistUpdateAtInfo\"[^>]*.\([^<]*)";
    //书籍类型const char * pattern = "href=\"/bookstore/\\\?classId=[^>]*.\([^<]*)";
    //书单简介const char * pattern = "BookInfoIntro\"[^>]*.[^>]*.[^>]*.\([^<]*)";
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
            strncpy(BookInfo.BookName,tmp,len+1);
            break;
        case '3' :
            printf("读取书单作者\n" );
            strncpy(BookInfo.BooklistAuthor,tmp,len+1);
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
            strncpy(BookInfo.BooklistIntro,tmp,len+1);
            break;
        case '7':
            printf("读取书单更新时间\n");
            strncpy(BookInfo.BooklistUpdata,tmp,len+1);
            break;
        default :
            printf("无效的flag,不能读取\n" );
        }
        p = p + len + (pmatch[0].rm_eo - pmatch[1].rm_eo);
        printf("%s\n",tmp);
    }
    if(flag == '4')
    {
        strcpy(BookInfo.BooklistViews,BooklistValue[0]);
        strcpy(BookInfo.BooklistCount,BooklistValue[1]);
        strcpy(BookInfo.BooklistKeep,BooklistValue[2]);
    }
    if(flag == '5')
    {
        BookInfo.BookTypeNum = booktype;
        for(int i = 0;i < booktype;i++)
        {
            strcat(BookInfo.BookType,BookType[i]);
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
    printf("%s\n",BookInfo.BookName);
    printf("%s\n",BookInfo.BooklistAuthor);
    printf("%s   ",BookInfo.BooklistViews);
    printf("%s   ",BookInfo.BooklistCount);
    printf("%s   \n",BookInfo.BooklistKeep);
    printf("%s    \n",BookInfo.BookType);
    printf("%s\n",BookInfo.BooklistUpdata);
    printf("%s\n",BookInfo.BooklistIntro);
    return 0;
}
int BooklistParsing(char* BooklistId)
{
    i = 0;
    char flag = '1';
    int booknum = 0;
    char urlpage[20] = "?page=2";
    char pageurl[200];
    const char * pattern[10];
    memset(pageurl,0,sizeof(pageurl));
    pattern [1] = "href=\"\\s*/\(book/[0-9]{1,6})\\s*";
    pattern [2] = "class=\"BookName\"[^>]*.\([^<]*)\\s*";
    pattern [3] = "userName\":\"\([^\"]*)\"},\"title\"";
    pattern [4] = "class=\"number-border-itemvalue\"[^>]*.\([^<]*)";
    pattern [5] = "href=\"/bookstore/\\\?classId=[^>]*.\([^<]*)";
    pattern [6] = "BookInfoIntro\"[^>]*.[^>]*.[^>]*.\([^<]*)";
    pattern [7] = "class=\"BooklistUpdateAtInfo\"[^>]*.\([^<]*)";
    char booklistid[100] = "test4.txt";
    char* url = "https://www.yousuu.com/booklist/5a405904da8315b47e51cbb6";
    //getinfo(booklistid,url);
    for(int i = 1;i < 8;i++)
    {
        regex(booklistid,pattern[i],flag);
        flag++;
    }
    readBLInfo(i);
    booknum = BookInfo.BooklistCount[0] - '0';
    printf("%d\n",booknum);
    for(int i = 1;i < (int)strlen(BookInfo.BooklistCount);i++)
    {
        booknum = (booknum * 10) + (BookInfo.BooklistCount[i] - '0');
        i++;
    }
    printf("%d\n  %s  %d\n",booknum,BookInfo.BooklistCount,(int)strlen(BookInfo.BooklistCount));
    if(booknum > 20)
    {
        int n = booknum / 20;
        printf("\n%d \n",n);
        if(booknum % 20 != 0)
        {
            n++;
        }
        printf("%d\n",n);
        booklistid[4]++;
        printf("booklistid : %s    ",booklistid);
        for(int i = 2, flag = '1';i <= n;i++)
        {
            strcpy(pageurl,url);
            strcat(pageurl,urlpage);
            printf("pageurl : %s\n  url : %s\n urlpage :%s\n booklistid : %s\n",pageurl,url,urlpage,booklistid);
            getinfo(booklistid,pageurl);
            regex(booklistid,pattern[1],flag);
            urlpage[6] ++;
            booklistid[4]++;
        }
    }
    readBLInfo(i);
    return 0;
}
