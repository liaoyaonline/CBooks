#include <stdio.h>
#include "mysqlplus.h"

int main()
{
    char booksid[100];
    MysqlDownload(booksid,"ing");
    printf("%s\n",booksid);
    return 0;
}

