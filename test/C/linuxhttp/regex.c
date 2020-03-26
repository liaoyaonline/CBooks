#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>
int main(int argc,char** argv)
{
    int n,len,count;
    int t;
    char buffer[512];
    regmatch_t pmatch[2];
    const size_t nmatch = 2;
    regex_t reg;
    char str[1024*1024];
    char *p = NULL;
    const char * pattern = "href=\"\\s*/\(book/[0-9]{1,6}\)\\s*";
    memset(str,0,sizeof(str));
    n = 0;
    count = 0;
    int fd = open(argv[1],O_RDONLY);
    if(fd < 0)
    {
        printf("file: %s open error\n",argv[1]);
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
        p = p + len + (pmatch[0].rm_eo - pmatch[1].rm_eo);
        printf("%s\n",tmp);
    }
    return 0;
}

