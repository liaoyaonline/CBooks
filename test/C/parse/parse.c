#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static const char * HREF_PATTERN = "href=\"\\s*\\([^ >\"]*\\)\\s*\"";

int main(int argc, char** argv){
    int n ,len, count;
    regex_t re;
    const size_t nmatch = 2;
    regmatch_t matchptr[nmatch];
    char *p = NULL;
    char str[1024*1024];

    memset(str, 0, sizeof(str));
    n = 0;
    count = 0;

    //operate file and read contents
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("file:%s open error\n", argv[1]);
        return -1;
    }
    
    while ((n = read(fd, str+count, 1024)) != 0) {
        if (n == -1) {
            printf("file read error\n");
            return -1;
        }
        
        count += n;

    }
    close(fd);
    printf("\nfile read over! begin URL analyse now...\n");

    p = str;

    if (regcomp(&re, HREF_PATTERN, 0) != 0) {/* compile error */
        printf("compile regex error\n");
    }

    while (regexec(&re, p, nmatch, matchptr, 0) != REG_NOMATCH) {
        len = (matchptr[1].rm_eo - matchptr[1].rm_so);
        p = p + matchptr[1].rm_so;
        char *tmp = (char *)calloc(len+1, 1);
        strncpy(tmp, p, len);
        tmp[len] = '\0';
        p = p + len + (matchptr[0].rm_eo - matchptr[1].rm_eo);
        printf("%s\n", tmp);
    }

    return 0;
}
