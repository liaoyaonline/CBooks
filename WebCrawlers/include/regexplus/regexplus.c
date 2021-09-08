#include <curl/curl.h>
#include <fcntl.h>
#include <mysql/mysql.h>
#include <regex.h>
#include <string.h>
#include <unistd.h>
#include "regexplus.h"
#include "mysqlplus.h"
int regexbookfile(char *booklistid, const char *pattern, char flag) {
  int n, len, count;
  int t;
  char buffer[512];
  regmatch_t pmatch[2];
  const size_t nmatch = 2;
  regex_t reg;
  char str[1024 * 1024];
  char *p = NULL;
  memset(str, 0, sizeof(str));
  n = 0;
  count = 0;
  int fd = open(booklistid, O_RDONLY);
  if (fd < 0) {
    printf("file: %s open error\n", booklistid);
    return -1;
  }
  while ((n = read(fd, str + count, 1024)) != 0) {
    if (n == -1) {
      printf("file read error\n");
      return -1;
    }
    count += n;
  }
  close(fd);
  printf("\nfile read over! begn URL analyse now...\n");

  p = str;

  if ((t = regcomp(&reg, pattern, REG_EXTENDED)) != 0) {
    regerror(t, &reg, buffer, sizeof buffer);
    fprintf(stderr, "grep: %s (%s)\n", buffer, pattern);
    return -1;
  }
  fprintf(stderr, "grep: %s (%s)\n", buffer, pattern);
  while (regexec(&reg, p, nmatch, pmatch, 0) != REG_NOMATCH) {
    len = (pmatch[1].rm_eo - pmatch[1].rm_so);
    p = p + pmatch[1].rm_so;
    char *tmp = (char *)calloc(len + 1, 1);
    strncpy(tmp, p, len);
    tmp[len] = '\0';
    switch (flag) {
      case 'a':
        printf("读取书名\n");
        strncpy(BookInfo.BookName, tmp, len + 1);
        break;
      case 'b':
        printf("读取作者名\n");
        strncpy(BookInfo.BookAuthor, tmp, len + 1);
        break;
      case 'c':
        printf("读取书本字数\n");
        strncpy(BookInfo.BookWordCount, tmp, len + 1);
        break;
      case 'd':
        printf("读取书本更新状态\n");
        strncpy(BookInfo.Bookstatus, tmp, len + 1);
        break;
      case 'e':
        printf("读取书本更新时间\n");
        strncpy(BookInfo.BookUpdata, tmp, len + 1);
        break;
      case 'f':
        printf("读取书本总评分\n");
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
        strncpy(BookInfo.BookClass, tmp, len + 1);
        break;
      case 'n':
        printf("读取添加这本书的书单总数\n");
        BookInfo.AddListCount = atoi(tmp);
        break;
      case 'o':
        printf("读取书本的介绍\n");
        strncpy(BookInfo.BookIntro, tmp, len + 1);
        break;
      case 'p':
        printf("读取添加这本书的书单号\n");
        strncpy(BooklistId[CurrBLNum], tmp, len + 1);
        CurrBLNum++;
        break;
      default:
        printf("无效的flag,不能读取\n");
    }
    p = p + len + (pmatch[0].rm_eo - pmatch[1].rm_eo);
    printf("%s\n", tmp);
  }
  return 0;
}
int getinfo(char *booklistid, char *url) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    FILE *fp;
    fp = fopen(booklistid, "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallBackFileWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    fclose(fp);

    if (CURLE_OK == res) {
      char *ct;
      /* ask for the content-type */
      res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

      if ((CURLE_OK == res) && ct) printf("We received Content-Type: %s\n", ct);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
int readBookInfo(int booknum) {
  for (int i = 0; i < booknum; i++) {
    printf("%s\n", BooklistId[i]);
  }
  printf("%s\n", BookInfo.BookName);
  printf("%s\n", BookInfo.BookAuthor);
  printf("%s   \n", BookInfo.BookWordCount);
  printf("%s   \n", BookInfo.Bookstatus);
  printf("%s   \n", BookInfo.BookUpdata);
  printf("%.1f    \n", BookInfo.BookScore);
  printf("%d\n", BookInfo.BookScoreCount);
  printf("%.2f\n", BookInfo.OneStarRate);
  printf("%.2f\n", BookInfo.TwoStarRate);
  printf("%.2f\n", BookInfo.ThreeStarRate);
  printf("%.2f\n", BookInfo.FourStarRate);
  printf("%.2f\n", BookInfo.FiveStarRate);
  printf("%s\n", BookInfo.BookClass);
  printf("%d\n", BookInfo.AddListCount);
  printf("%s\n", BookInfo.BookIntro);
  return 0;
}
int regexbook(char *inbookid) {
  if (strlen(inbookid) > 6) {
    printf("in bookid error! %ld\n", strlen(inbookid));
    return -1;
  }
  BlInfo *pblist = &BooklistInfo;
  BInfo *pbook = &BookInfo;
  CurrBLNum = 0;
  int Inquire = 0;
  int Inquirebldone = 0;
  int Inquirenotnull = 0;
  char Attribute[3][40];
  strcpy(Attribute[0], "BookId");
  strcpy(Attribute[1], "BooklistId");
  strcpy(Attribute[2], "BooksId");
  int booklistsnum = 0;
  int pagenum = 0;
  char booklisturl[400];
  char bookurl[400];
  char booklistid[40];
  int page = 1;
  const char *pattern[20];
  char bookid[100];
  memset(bookid, 0, sizeof(bookid));
  char TargetTable[3][100];
  strcpy(TargetTable[0], "BookDone");
  strcpy(TargetTable[1], "BooklistDone");
  strcpy(TargetTable[2], "ing");
  char frontblurl[100] = "https://www.yousuu.com/api/book/";
  char frontburl[100] = "https://www.yousuu.com/book/";
  char urlpage[20] = "/booklist?page=";
  pattern[1] = "class=\"book-name\"[^>]*.\([^<]*)";
  pattern[2] = "class=\"book-author[^>]*.[^>]*.\([^<]*)";
  pattern[3] = "class=\"book-word-count[^>]*.\([^<]*)";
  pattern[4] = "class=\"status[^>]*.\([^<]*)";
  pattern[5] = "class=\"book-status[^>]*.\\s*\([^<]*)";
  pattern[6] = "\"score\":\([^,]*),\"score";
  pattern[7] = "\"scorerCount\":\([^,]*),\"";
  pattern[8] =
      "scoreDetail\":\\\[\([^,]*),";  //会有两个相同的数据，用后一个覆盖即可
  pattern[9] = "scoreDetail\":\\\[\[^,]*,([^,]*),";
  pattern[10] = "scoreDetail\":\\\[\[^,]*,[^,]*,\([^,]*),";
  pattern[11] = "scoreDetail\":\\\[\[^,]*,[^,]*,[^,]*,\([^,]*),";
  pattern[12] = "scoreDetail\":\\\[\[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*)]";
  pattern[13] = "\"tags\":\\\[\([^]]*)";
  pattern[14] = "class=\"addListCount[^>]*.\([^<]*)";
  pattern[15] = "\"introduction\":.\([^\"]*)";
  pattern[16] = "class=\"booklist-card\"[^\"]*./booklist/\([^\"]*)";
  pattern[17] =
      "\"booklistId\":\"\([^\"]*)";  // https://www.yousuu.com/api/book/176584/booklist?page=4使用这个格式爬取，同时解析这里面的id
  char flag = 'a';
  strcpy(bookid, inbookid);
  printf("test bookid :%s\n", bookid);
  Inquire = MysqlInquire(bookid, TargetTable[2], Attribute[2]);
  if (Inquire > 0) {
    MysqlDelete(bookid, TargetTable[2], Attribute[2]);
    printf("delete id: %s\n", bookid);
  } else {
    printf("id error ,not found from ing :%s\n", bookid);
    return -2;
  }

  strcpy(BookInfo.BookId, bookid);              //将ｉｄ信息写入结构体
  sprintf(bookurl, "%s%s", frontburl, bookid);  //建立对应的ｕｒｌ
  printf("%s\n", bookurl);
  getinfo(bookid, bookurl);     //爬取书本对应网页保存到bookid里面
  for (int i = 1; i < 16; i++)  //对网页进行解析，读取有用信息
  {
    regexbookfile(bookid, pattern[i], flag);
    flag++;
  }
  readBookInfo(CurrBLNum);  //读取爬取到的结构体内容
  Inquire = MysqlInquire(bookid, TargetTable[0], Attribute[0]);
  Inquirenotnull =
      strlen(BookInfo.BookName) +
      strlen(
          BookInfo
              .BookAuthor);  //检测不是空白网页爬取,因为每次爬取完这两个值会重置
  if (Inquire == 0 && Inquirenotnull != 0)
    MysqlUpload(pblist, pbook, BooklistId[0], TargetTable[0],
                '1');  //将爬取到的书本信息上传到bookdone表里面
  booklistsnum = BookInfo.AddListCount;  //计算书本数目
  printf("%d\n", booklistsnum);
  if (booklistsnum > 0) {
    pagenum = booklistsnum / 20;
    if (booklistsnum % 20 != 0) pagenum++;
  }
  printf("%d\n", pagenum);
  if (pagenum > 0)  //爬取书本对应的书单列表
  {
    for (int i = 1; i <= pagenum; i++) {
      sprintf(booklisturl, "%s%s%s%d", frontblurl, bookid, urlpage, page);
      printf("%s\n", booklisturl);
      sprintf(booklistid, "%sbl%d", bookid, page);
      printf("%s\n", booklistid);
      getinfo(booklistid, booklisturl);
      regexbookfile(booklistid, pattern[17], 'p');
      page++;
    }
  }
  readBookInfo(CurrBLNum);  //读取所有爬取结果
  for (int i = 0; i < booklistsnum;
       i++)  //将爬取到的书单ｉｄ，将不在ing里面的ｉｄ上传到ing里面
  {
    Inquire = MysqlInquire(BooklistId[i], TargetTable[2], Attribute[2]);
    Inquirebldone = MysqlInquire(BooklistId[i], TargetTable[1], Attribute[1]);
    Inquirenotnull = strlen(BooklistId[i]);  //检测数据不为空
    if (Inquire == 0 && Inquirebldone == 0 && Inquirenotnull != 0)
      MysqlUpload(pblist, pbook, BooklistId[i], TargetTable[2], '3');
  }
  return 0;
}
int regexblfile(char *booklistid, const char *pattern, char flag) {
  int n, len, count;
  int t;
  char BooklistValue[3][20];
  char BookType[40][40];
  int value = 0;
  int booktype = 0;
  char buffer[512];
  regmatch_t pmatch[2];
  const size_t nmatch = 2;
  regex_t reg;
  char str[1024 * 1024];
  char *p = NULL;
  //书号const char * pattern = "href=\"\\s*/\(book/[0-9]{1,6}\)\\s*";
  // name const char * pattern = "class=\"booklistName\"[^>]*.\([^<]*)\\s*";
  //作者 const char * pattern = "userName\":\"\([^\"]*)\"},\"title\"";
  //浏览，书本数目，收藏123..const char * pattern =
  //"class=\"number-border-itemvalue\"[^>]*.\([^<]*)"; 更新时间const char *
  //pattern = "class=\"BooklistUpdateAtInfo\"[^>]*.\([^<]*)"; 书籍类型const char
  //* pattern = "href=\"/bookstore/\\\?classId=[^>]*.\([^<]*)"; 书单简介const
  //char * pattern = "BooklistInfoIntro\"[^>]*.[^>]*.[^>]*.\([^<]*)";
  memset(str, 0, sizeof(str));
  n = 0;
  count = 0;
  int fd = open(booklistid, O_RDONLY);
  if (fd < 0) {
    printf("file: %s open error\n", booklistid);
    return -1;
  }
  while ((n = read(fd, str + count, 1024)) != 0) {
    if (n == -1) {
      printf("file read error\n");
      return -1;
    }
    count += n;
  }
  close(fd);
  printf("\nfile read over! begn URL analyse now...\n");

  p = str;

  if ((t = regcomp(&reg, pattern, REG_EXTENDED)) != 0) {
    regerror(t, &reg, buffer, sizeof buffer);
    fprintf(stderr, "grep: %s (%s)\n", buffer, pattern);
    return -1;
  }
  fprintf(stderr, "grep: %s (%s)\n", buffer, pattern);
  while (regexec(&reg, p, nmatch, pmatch, 0) != REG_NOMATCH) {
    len = (pmatch[1].rm_eo - pmatch[1].rm_so);
    p = p + pmatch[1].rm_so;
    char *tmp = (char *)calloc(len + 1, 1);
    strncpy(tmp, p, len);
    tmp[len] = '\0';
    switch (flag) {
      case '1':
        printf("读取书单内书号\n");
        strncpy(BookId[i], tmp, len + 1);
        i++;
        break;
      case '2':
        printf("读取书单名称\n");
        strncpy(BooklistInfo.BooklistName, tmp, len + 1);
        break;
      case '3':
        printf("读取书单作者\n");
        strncpy(BooklistInfo.BooklistAuthor, tmp, len + 1);
        break;
      case '4':
        printf("读取书单基本信息\n");
        strncpy(BooklistValue[value], tmp, len + 1);
        value++;
        break;
      case '5':
        printf("读取书单类型\n");
        strncpy(BookType[booktype], tmp, len + 1);
        booktype++;
        break;
      case '6':
        printf("读取书单介绍\n");
        strncpy(BooklistInfo.BooklistIntro, tmp, len + 1);
        break;
      case '7':
        printf("读取书单更新时间\n");
        strncpy(BooklistInfo.BooklistUpdata, tmp, len + 1);
        break;
      default:
        printf("无效的flag,不能读取\n");
    }
    p = p + len + (pmatch[0].rm_eo - pmatch[1].rm_eo);
    printf("%s\n", tmp);
  }
  if (flag == '4') {
    strcpy(BooklistInfo.BooklistViews, BooklistValue[0]);
    BooklistInfo.BooklistCount = atoi(BooklistValue[1]);  //将字符类型转化为整数
    BooklistInfo.BooklistKeep = atoi(BooklistValue[2]);
  }
  if (flag == '5') {
    // BooklistInfo.BookTypeNum = booktype;
    for (int i = 0; i < booktype; i++) {
      strcat(BooklistInfo.BookType, BookType[i]);
    }
  }
  return 0;
}
int readBLInfo(int booknum) {
  for (int i = 0; i < booknum; i++) {
    printf("%s\n", BookId[i]);
  }
  printf("%s\n", BooklistInfo.BooklistName);
  printf("%s\n", BooklistInfo.BooklistAuthor);
  printf("%s   ", BooklistInfo.BooklistViews);
  printf("%d   ", BooklistInfo.BooklistCount);
  printf("%d   \n", BooklistInfo.BooklistKeep);
  printf("%s    \n", BooklistInfo.BookType);
  printf("%s\n", BooklistInfo.BooklistUpdata);
  printf("%s\n", BooklistInfo.BooklistIntro);
  return 0;
}
int BooklistParsing(char *BooklistId) {
  if (strlen(BooklistId) < 7) {
    printf("in booklistId is error! %ld\n", strlen(BooklistId));
    return -1;
  }
  BlInfo *pblist = &BooklistInfo;
  BInfo *pbook = &BookInfo;
  i = 0;
  int pagenum = 0;
  int Inquire = 0;
  int Inquirebdone = 0;
  int Inquirenotnull = 0;
  char Attribute[3][40];
  strcpy(Attribute[0], "BookId");
  strcpy(Attribute[1], "BooklistId");
  strcpy(Attribute[2], "BooksId");
  char TargetTable[3][100];
  strcpy(TargetTable[0], "BookDone");
  strcpy(TargetTable[1], "BooklistDone");
  strcpy(TargetTable[2], "ing");
  char flag = '1';
  int booknum = 0;
  char booklisturl[400];
  char booksurl[400];
  char booklistid[40];
  char booksid[100];
  char frontblurl[200] = "https://www.yousuu.com/booklist/";
  char urlpage[20] = "?page=";
  int page = 2;
  char pageurl[200];
  const char *pattern[10];
  memset(pageurl, 0, sizeof(pageurl));
  pattern[1] = "href=\"\\s*/book/\([0-9]{1,6})\\s*";
  pattern[2] = "class=\"booklistName\"[^>]*.\([^<]*)\\s*";
  pattern[3] = "userName\":\"\([^\"]*)\"},\"title\"";
  pattern[4] = "class=\"number-border-itemvalue\"[^>]*.\([^<]*)";
  pattern[5] = "href=\"/bookstore/\\\?classId=[^>]*.\([^<]*)";
  pattern[6] = "BooklistInfoIntro\"[^>]*.[^>]*.[^>]*.\([^<]*)";
  pattern[7] = "class=\"BooklistUpdateAtInfo\"[^>]*.\([^<]*)";
  // getinfo(booklistid,url);
  strcpy(booklistid, BooklistId);
  printf("booklistid :%s\n", booklistid);
  Inquire = MysqlInquire(booklistid, TargetTable[2], Attribute[2]);
  if (Inquire > 0) {
    MysqlDelete(booklistid, TargetTable[2], Attribute[2]);
    printf("delete id: %s\n", booklistid);
  } else {
    printf("id error ,not found from ing :%s\n", booklistid);
    return -2;
  }
  strcpy(BooklistInfo.BooklistId, booklistid);  //将ｉｄ信息写入结构体
  sprintf(booklisturl, "%s%s", frontblurl, booklistid);  //建立对应的ｕｒｌ
  printf("URL:%s\n", booklisturl);
  getinfo(booklistid, booklisturl);
  for (int i = 1; i < 8; i++) {
    regexblfile(booklistid, pattern[i], flag);
    flag++;
  }
  readBLInfo(i);
  Inquire = MysqlInquire(booklistid, TargetTable[1], Attribute[1]);
  Inquirenotnull = strlen(BooklistInfo.BooklistName) +
                   strlen(BooklistInfo.BooklistAuthor);  //检测不是空白网页爬取
  if (Inquire == 0 && Inquirenotnull != 0)
    MysqlUpload(pblist, pbook, BookId[0], TargetTable[1],
                '2');  //将爬取到的书本信息上传
  booknum = BooklistInfo.BooklistCount;
  printf("%d\n   %d\n", booknum, BooklistInfo.BooklistCount);
  if (booknum > 0) {
    pagenum = booknum / 20;
    if (booknum % 20 != 0) pagenum++;
  }
  printf("%d\n", pagenum);
  if (pagenum > 0) {
    for (int i = 2, flag = '1'; i <= pagenum; i++) {
      sprintf(booksurl, "%s%s%s%d", frontblurl, booklistid, urlpage,
              page);  //建立对应的书本sfilename
      sprintf(booksid, "%sbooks%d", booklistid,
              page);  //建立对应的书本sfilename
      printf("booksId:%s\nbooksURL: %s\n", booksid, booksurl);
      getinfo(booksid, booksurl);
      regexblfile(booksid, pattern[1], flag);
      page++;
    }
  }
  readBLInfo(i);
  for (int i = 0; i < booknum;
       i++)  //将爬取到的书单ｉｄ，将不在ing里面的ｉｄ上传到ing里面
  {
    Inquire = MysqlInquire(BookId[i], TargetTable[2], Attribute[2]);
    Inquirebdone = MysqlInquire(BookId[i], TargetTable[0], Attribute[0]);
    Inquirenotnull = strlen(BookId[i]);  //该空间内不为空没有经过测试
    if (Inquire == 0 && Inquirebdone == 0 && Inquirenotnull != 0)
      MysqlUpload(pblist, pbook, BookId[i], TargetTable[2], '3');
  }
  return 0;
}
int InitBooks() {
  memset(BookInfo.BookId, 0, sizeof(BookInfo.BookId));
  memset(BookInfo.BookName, 0, sizeof(BookInfo.BookName));
  memset(BookInfo.BookAuthor, 0, sizeof(BookInfo.BookAuthor));
  memset(BookInfo.BookWordCount, 0, sizeof(BookInfo.BookWordCount));
  memset(BookInfo.Bookstatus, 0, sizeof(BookInfo.Bookstatus));
  memset(BookInfo.BookUpdata, 0, sizeof(BookInfo.BookUpdata));
  BookInfo.BookScore = 0;
  BookInfo.BookScoreCount = 0;
  BookInfo.OneStarRate = 0;
  BookInfo.TwoStarRate = 0;
  BookInfo.ThreeStarRate = 0;
  BookInfo.FourStarRate = 0;
  BookInfo.FiveStarRate = 0;
  memset(BookInfo.BookClass, 0, sizeof(BookInfo.BookClass));
  BookInfo.AddListCount = 0;
  memset(BookInfo.BookIntro, 0, sizeof(BookInfo.BookIntro));
  memset(BooklistInfo.BooklistId, 0, sizeof(BooklistInfo.BooklistId));
  memset(BooklistInfo.BooklistName, 0, sizeof(BooklistInfo.BooklistName));
  memset(BooklistInfo.BooklistAuthor, 0, sizeof(BooklistInfo.BooklistAuthor));
  memset(BooklistInfo.BooklistViews, 0, sizeof(BooklistInfo.BooklistViews));
  BooklistInfo.BooklistCount = 0;
  BooklistInfo.BooklistKeep = 0;
  memset(BooklistInfo.BookType, 0, sizeof(BooklistInfo.BookType));
  memset(BooklistInfo.BooklistUpdata, 0, sizeof(BooklistInfo.BooklistUpdata));
  memset(BooklistInfo.BooklistIntro, 0, sizeof(BooklistInfo.BooklistIntro));
  return 0;
}
