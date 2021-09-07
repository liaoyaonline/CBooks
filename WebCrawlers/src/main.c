#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mysqlplus.h"
#include "regexplus.h"
int main() {
  int sleeptime = 40;
  int Inquire = 0;
  char booksid[100];
  memset(booksid, 0, sizeof(booksid));
  printf("booksid:%s\n", booksid);
  for (int i = 0; i < 20000; i++) {
    MysqlDownload(booksid, "ing");  //从ing中取出url
    if (strlen(booksid) > 6) {
      Inquire = MysqlInquire(booksid, "BooklistDone",
                             "BooklistId");  //检测这个url没有被爬取过
      printf("%d\n", Inquire);
      if (Inquire == 0)
        BooklistParsing(
            booksid);  //爬取这个页面，进行解析，将结果存入对应数据库
      else
        MysqlDelete(booksid, "ing", "BooksId");  //在ing中删除这个url
    } else {
      Inquire = MysqlInquire(booksid, "BookDone", "BookId");
      printf("%d\n", Inquire);
      if (Inquire == 0)
        regexbook(booksid);
      else
        MysqlDelete(booksid, "ing", "BooksId");
    }
    InitBooks();
    memset(booksid, 0, sizeof(booksid));
    sleep(sleeptime);
  }
  printf("%s\n", booksid);
  // BooklistParsing(url);
  // regexbook(bookid);
  return 0;
}
