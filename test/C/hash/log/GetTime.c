#include<sys/time.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
void GetTime();
int main()
{
    GetTime();
    return 0;
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
}
