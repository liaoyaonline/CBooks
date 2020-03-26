#ifndef MYSQLPLUS_H_INCLUDED
#define MYSQLPLUS_H_INCLUDED

typedef struct Books
{
    char BookId[100];
    char BookName[100];
    char BookAuthor[100];
    char BookWordCount[100];
    char Bookstatus[40];
    char BookUpdata[100];
    char BookScore[100];
    char BookScoreCount[100];
    char OneStarRate[20];
    char TwoStarRate[20];
    char ThreeStarRate[20];
    char FourStarRate[20];
    char FiveStarRate[20];
    char BookClass[400];
    char AddListCount[20];
    char BookIntro[4000];
} BInfo;
typedef struct Booklists
{
    int BookTypeNum;
    char BooklistName[100];
    char BooklistId[100];
    char BooklistAuthor[100];
    char BooklistViews[20];
    char BooklistCount[20];
    char BooklistKeep[20];
    char BookType[400];
    char BooklistUpdata[100];
    char BooklistIntro[4000];
} BlInfo;


int MysqlUpload(BlInfo* uploadBL,BInfo * uploadB,char* uploadBS,char* TargetTable,char flag);
int MysqlDownload(char * Downloadurl,char* TargetTable);
int MysqlDelete(char * DeleteId,char* TargetTable,char* Attribute);
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute);



#endif
