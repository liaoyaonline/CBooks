#ifndef MYSQLPLUS_H_INCLUDED
#define MYSQLPLUS_H_INCLUDED



int MysqlUpload(BlInfo* uploadBL,BInfo * uploadB,char* uploadBS,char* TargetTable,char flag);
int MysqlDownload(char * Downloadurl,char* TargetTable);
int MysqlDelete(char * DeleteId,char* TargetTable,char* Attribute);
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute);



#endif
