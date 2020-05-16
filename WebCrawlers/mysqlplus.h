#ifndef MYSQLPLUS_H_INCLUDED
#define MYSQLPLUS_H_INCLUDED

typedef struct Books
{
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
typedef struct Booklists
{
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


int MysqlUpload(BlInfo* uploadBL,BInfo * uploadB,char* uploadBS,char* TargetTable,char flag);
int MysqlDownload(char * Downloadurl,char* TargetTable);
int MysqlDelete(char * DeleteId,char* TargetTable,char* Attribute);
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute);



#endif
