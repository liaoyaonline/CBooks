#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include "regexplus.h"
int regexbookfile(char* booklistid,const char* pattern,char flag)
{
    int n,len,count;
    int t;
    char buffer[512];
    regmatch_t pmatch[2];
    const size_t nmatch = 2;
    regex_t reg;
    char str[1024*1024];
    char *p = NULL;
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
        case 'a' :
            printf("读取书名\n" );
            strncpy(BookInfo.BookName,tmp,len+1);
            break;
        case 'b' :
            printf("读取作者名\n");
            strncpy(BookInfo.BookAuthor,tmp,len+1);
            break;
        case 'c' :
            printf("读取书本字数\n" );
            strncpy(BookInfo.BookWordCount,tmp,len+1);
            break;
        case 'd' :
            printf("读取书本更新状态\n" );
            strncpy(BookInfo.Bookstatus,tmp,len+1);
            break;
        case 'e' :
            printf("读取书本更新时间\n" );
            strncpy(BookInfo.BookUpdata,tmp,len+1);
            break;
        case 'f' :
            printf("读取书本总评分\n" );
            BookInfo.BookScore = atof(tmp);
            break;
        case 'g':
            printf("读取书本评分人数\n");
            BookInfo.BookScoreCount = atoi(tmp);
            break;
        case 'h':
            printf("读取评一星占比\n");
            BookInfo.OneStarRate = atof(tmp);
            break;
        case 'i':
            printf("读取二星占比\n");
            BookInfo.TwoStarRate = atof(tmp);
            break;
        case 'j':
            printf("读取评三星占比\n");
            BookInfo.ThreeStarRate = atof(tmp);
            break;
        case 'k':
            printf("读取评四星占比\n");
            BookInfo.FourStarRate = atof(tmp);
            break;
        case 'l':
            printf("读取评五星占比\n");
            BookInfo.FiveStarRate = atof(tmp);
            break;
        case 'm':
            printf("读取书本类型\n");
            strncpy(BookInfo.BookClass,tmp,len+1);
            break;
        case 'n':
            printf("读取添加这本书的书单总数\n");
            BookInfo.AddListCount = atoi(tmp);
            break;
        case 'o':
            printf("读取书本的介绍\n");
            strncpy(BookInfo.BookIntro,tmp,len+1);
            break;
        case 'p':
            printf("读取添加这本书的书单号\n");
            strncpy(BooklistId[CurrBLNum],tmp,len+1);
            CurrBLNum++;
            break;
        default :
            printf("无效的flag,不能读取\n" );
        }
        p = p + len + (pmatch[0].rm_eo - pmatch[1].rm_eo);
        printf("%s\n",tmp);
    }
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
