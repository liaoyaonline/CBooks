#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "hash.h"

char OffsetUrl[80];
void get();
void parse();
void GetTime();
void Traversal();
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
    while(TimeSize < 1)
    {
        TimeSize++;
        GetTime();
        FILE *flog = fopen("log.txt","a+");
        FILE *fp = fopen("ing.txt","r");
        memset(OffsetUrl,0,sizeof(OffsetUrl));
        fscanf(fp,"%s",OffsetUrl);
        fprintf(flog,"\t读取Url:%s \n",OffsetUrl);
        if(feof(fp))
        {
            fclose(fp);
            fclose(flog);
            break;
        }
        GetResult = GetHashNode(OffsetUrl);
        if(GetResult == 1)
        {
            fprintf(flog,"\t该Url：%s在hashmap里面已经存在\n",OffsetUrl);
            system("sed -i '1d' ing.txt");
            fclose(fp);
            fclose(flog);
            continue;
        }
        srand((unsigned)time(NULL));
        SleepTime = (rand() % 50 +1);
        fprintf(flog,"\t该Url: %s在hashmap里面不存在，开始爬取\n",OffsetUrl);
        fprintf(flog,"\t休眠 %d s\n",SleepTime);
        sleep(SleepTime);
        get();
        parse();
        system("sed -i '1d' ing.txt");
        fprintf(flog,"\t对页面进行解析，爬取出来的数据,加入result.txt,爬出来的网址加入UrlTmp.txt\n\tUrl如下:\n");
        fclose(flog);
        Traversal();
        fCheckUrl();
        system("sed -i '1d' ing.txt");
        NodeNum = Hash(OffsetUrl);
        PutHashmap(NodeNum);
        //fprintf(flog,"将该Url压入hashmap:OffsetUrl: %s NodeNum:%d\n",OffsetUrl,NodeNum);
        readnode();
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
void GetTime()
{
    FILE *fp = fopen("log.txt","a+");
    struct timeval tv;
    gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
    uint64_t sec=tv.tv_sec;
    uint64_t min=tv.tv_sec/60;
    struct tm cur_tm;//保存转换后的时间结果
    localtime_r((time_t*)&sec,&cur_tm);
    char cur_time[20];
    snprintf(cur_time,20,"%d-%02d-%02d %02d:%02d:%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
    fprintf(fp,"Time:%s\n",cur_time);//打印当前时间
    fclose(fp);
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
        fprintf(fw,"\t%s\n",UrlTmp);
    }
    fclose(fr);
    fclose(fw);
}
