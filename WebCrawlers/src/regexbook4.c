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
#include "mysqlplus.h"
int main()
{
    int sleeptime = 40;
    int Inquire = 0;
    char booksid[100];
    memset(booksid,0,sizeof(booksid));
    printf("booksid:%s\n",booksid);
    for(int i = 0;i < 20000;i++)
    {
        MysqlDownload(booksid,"ing");
        if(strlen(booksid) > 6)
        {
            Inquire = MysqlInquire(booksid,"BooklistDone","BooklistId");
            printf("%d\n",Inquire);
            if(Inquire == 0)
                BooklistParsing(booksid);
            else
                MysqlDelete(booksid,"ing","BooksId");
        }
        else
        {
            Inquire = MysqlInquire(booksid,"BookDone","BookId");
            printf("%d\n",Inquire);
            if(Inquire == 0)
                regexbook(booksid);
            else
                MysqlDelete(booksid,"ing","BooksId");
        }
        InitBooks();
        memset(booksid,0,sizeof(booksid));
        sleep(sleeptime);
    }
    printf("%s\n",booksid);
    //BooklistParsing(url);
    //regexbook(bookid);
    return 0;
}
