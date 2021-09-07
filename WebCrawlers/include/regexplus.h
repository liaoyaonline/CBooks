#ifndef REGEXPLUS_H_INCLUDED
#define REGEXPLUS_H_INCLUDED

typedef struct Books {
  char BookId[100];
  char BookName[200];
  char BookAuthor[100];
  char BookWordCount[100];
  char Bookstatus[40];
  char BookUpdata[100];
  float BookScore;
  int BookScoreCount;
  float OneStarRate;
  float TwoStarRate;
  float ThreeStarRate;
  float FourStarRate;
  float FiveStarRate;
  char BookClass[400];
  int AddListCount;
  char BookIntro[20000];
} BInfo;
typedef struct Booklists {
  char BooklistName[100];
  char BooklistId[100];
  char BooklistAuthor[100];
  char BooklistViews[20];
  int BooklistCount;
  int BooklistKeep;
  char BookType[400];
  char BooklistUpdata[100];
  char BooklistIntro[10000];
} BlInfo;
BInfo BookInfo;
BlInfo BooklistInfo;
char BooklistId[4000][80];
char BookId[1000][80];
int CurrBLNum;
int i;

int regexbookfile(char* booklistid, const char* pattern, char flag);
int getinfo(char* booklistid, char* url);
int readBookInfo(int booknum);
int regexbook(char* inbookid);
int regexblfile(char* booklistid, const char* pattern, char flag);
int readBLInfo(int booknum);
int BooklistParsing(char* BooklistId);
int InitBooks();
static size_t curlCallBackFileWrite(void* buffer, size_t size, size_t nmemb,
                                    void* stream) {
  int written = fwrite(buffer, size, nmemb, (FILE*)stream);
  return written;
}
#endif
