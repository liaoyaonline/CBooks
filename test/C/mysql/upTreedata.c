#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
typedef struct Books
{
    char BookId[100];
    char BookName[100];
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
    char BookIntro[4000];
    char Result;
} BInfo;
BInfo BookInfo;
int MysqlDownData(char * Downloadurl,char* TargetTable);
int MysqlUpload(BInfo * uploadB,char* TargetTable,char flag);
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute);
int MysqlDelete(char * DeleteId,char* TargetTable,char* Attribute);
int InitBooks();
int readBookInfo();
int main()
{
    int sleeptime = 3;
    char flag = '1';
    int result = 6;
    int checkresult = 0;
    int inquireTrain = 0;
    int inquireTest = 0;
    BInfo * pB = &BookInfo;
    printf("Hello world\n");
    char TargetTable[3][100];
    char Attribute[100] = "BookId";
    strcpy(TargetTable[0],"TreeData");
    strcpy(TargetTable[1],"TrainsetData");
    strcpy(TargetTable[2],"TestsetData");
    for(int i = 0;i < 200;i++)
    {
        MysqlDownData(BookInfo.BookId,TargetTable[0]);
        readBookInfo();
        printf("输入1表示这本书符合你胃口，输入0表示这本书不符合你胃口,输入5表示没看过这本书\n");
        scanf("%d",&result);
        BookInfo.Result = result;
        inquireTrain = MysqlInquire(BookInfo.BookId,TargetTable[1],Attribute);
        inquireTest = MysqlInquire(BookInfo.BookId,TargetTable[2],Attribute);
        if(BookInfo.Result == 0 || BookInfo.Result == 1 || BookInfo.Result == 5)
            checkresult = 1;
        if(inquireTrain == 0 && inquireTest == 0 && checkresult == 1)
        {
            if(BookInfo.Result == 5)
                MysqlUpload(pB,TargetTable[2],flag);
            else
                MysqlUpload(pB,TargetTable[1],flag);
            MysqlDelete(BookInfo.BookId,TargetTable[0],Attribute);
        }
        InitBooks();
        readBookInfo();
        sleep(sleeptime);
    }
    return 0;
}
int MysqlDownData(char * Downloadurl,char* TargetTable)
{
    MYSQL *conn_ptr;
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char sql_down[200];
    memset(sql_down,0,sizeof(sql_down));
    sprintf(sql_down,"select * from %s order by AddListCount desc limit 1;",TargetTable);
    conn_ptr = mysql_init(NULL);//初始化
    if(!conn_ptr)
    {
        printf("mysql_init failed!\n");
        return -1;
    }

    ret = mysql_options(conn_ptr,MYSQL_OPT_CONNECT_TIMEOUT,(const char*)&timeout);//设置超时选项
    if(ret)
    {
        printf("Options Set ERRO!\n");
    }
    conn_ptr = mysql_real_connect(conn_ptr,"localhost","root","123","books",0,NULL,0);//连接MySQL testdb数据库
    if(conn_ptr)
    {
        printf("Connection Succeed!\n");
        mysql_set_character_set(conn_ptr, "utf8");

        ret = mysql_query(conn_ptr,sql_down); //执行SQL语句
        if(!ret)
        {
            printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(conn_ptr));//返回上次UPDATE更改行数
        }
        else
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
        }
        res = mysql_use_result(conn_ptr);
        while((row = mysql_fetch_row(res)) != NULL)
        {
            printf("%s\n",row[0]);
            strcpy(Downloadurl,row[0]);
            strcpy(BookInfo.BookName,row[1]);
            strcpy(BookInfo.BookAuthor,row[2]);
            strcpy(BookInfo.BookWordCount,row[3]);
            strcpy(BookInfo.Bookstatus,row[4]);
            strcpy(BookInfo.BookUpdata,row[5]);
            BookInfo.BookScore = atof(row[6]);
            BookInfo.BookScoreCount = atoi(row[7]);
            BookInfo.OneStarRate = atof(row[8]);
            BookInfo.TwoStarRate = atof(row[9]);
            BookInfo.ThreeStarRate = atof(row[10]);
            BookInfo.FourStarRate = atof(row[11]);
            BookInfo.FiveStarRate = atof(row[12]);
            strcpy(BookInfo.BookClass,row[13]);
            BookInfo.AddListCount = atoi(row[14]);
            strcpy(BookInfo.BookIntro,row[15]);
        }
        mysql_free_result(res);
        mysql_close(conn_ptr);
        printf("Connection closed!\n");
    }
    else    //错误处理
    {
        printf("Connection Failed!\n");
        if(mysql_errno(conn_ptr))
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
        }
        return -2;
    }

    return 0;
}
int readBookInfo()
{
    printf("%s\n",BookInfo.BookId);
    printf("%s\n",BookInfo.BookName);
    printf("%s\n",BookInfo.BookAuthor);
    printf("%s   \n",BookInfo.BookWordCount);
    printf("%s   \n",BookInfo.Bookstatus);
    printf("%s   \n",BookInfo.BookUpdata);
    printf("%.1f    \n",BookInfo.BookScore);
    printf("%d\n",BookInfo.BookScoreCount);
    printf("%.2f\n",BookInfo.OneStarRate);
    printf("%.2f\n",BookInfo.TwoStarRate);
    printf("%.2f\n",BookInfo.ThreeStarRate);
    printf("%.2f\n",BookInfo.FourStarRate);
    printf("%.2f\n",BookInfo.FiveStarRate);
    printf("%s\n",BookInfo.BookClass);
    printf("%d\n",BookInfo.AddListCount);
    printf("%s\n",BookInfo.BookIntro);
    return 0;
}
int MysqlUpload(BInfo * uploadB,char* TargetTable,char flag)
{
    MYSQL *conn_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char sql_insert[6000];
    switch(flag)
    {
    case '1':
        printf("上传到TrainsetData\n");
        sprintf(sql_insert, "INSERT INTO %s(BookId,BookName,BookUpdata,BookScore,BookScoreCount,OneStarRate,TwoStarRate,ThreeStarRate,FourStarRate,FiveStarRate,AddListCount,BookIntro,Result) VALUES('%s','%s','%s','%.1f','%d','%.2f','%.2f','%.2f','%.2f','%.2f','%d','%s','%d');",TargetTable, uploadB->BookId,uploadB->BookName,uploadB->BookUpdata,uploadB->BookScore,uploadB->BookScoreCount,uploadB->OneStarRate,uploadB->TwoStarRate,uploadB->ThreeStarRate,uploadB->FourStarRate,uploadB->FiveStarRate,uploadB->AddListCount,uploadB->BookIntro,uploadB->Result);
        break;
    case '2':
        printf("上传到TestsetData\n");
        //sprintf(sql_insert, "INSERT INTO %s(BooklistId,BooklistName,BooklistAuthor,BooklistViews,BooklistCount,BooklistKeep,BookType,BooklistUpdata,BooklistIntro) VALUES('%s','%s','%s','%s','%d','%d','%s','%s','%s');",TargetTable, uploadBL->BooklistId,uploadBL->BooklistName,uploadBL->BooklistAuthor,uploadBL->BooklistViews,uploadBL->BooklistCount,uploadBL->BooklistKeep,uploadBL->BookType,uploadBL->BooklistUpdata,uploadBL->BooklistIntro);
        printf("%s\n",sql_insert);
        break;
    case '3':
        printf("上传id\n");
        //sprintf(sql_insert,"INSERT INTO %s(BooksId) VALUES('%s');",TargetTable,uploadBS);
        break;
    default:
        printf("无效的flag,不能读取\n");
    }
    printf("%s\n",sql_insert);
    conn_ptr = mysql_init(NULL);//初始化
    if(!conn_ptr)
    {
        printf("mysql_init failed!\n");
        return -1;
    }

    ret = mysql_options(conn_ptr,MYSQL_OPT_CONNECT_TIMEOUT,(const char*)&timeout);//设置超时选项
    if(ret)
    {
        printf("Options Set ERRO!\n");
    }
    conn_ptr = mysql_real_connect(conn_ptr,"localhost","root","123","books",0,NULL,0);//连接MySQL testdb数据库
    if(conn_ptr)
    {
        printf("Connection Succeed!\n");
        mysql_set_character_set(conn_ptr, "utf8");

        ret = mysql_query(conn_ptr,sql_insert); //执行SQL语句
        if(!ret)
        {
            printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(conn_ptr));//返回上次UPDATE更改行数
        }
        else
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
        }

        mysql_close(conn_ptr);
        printf("Connection closed!\n");
    }
    else    //错误处理
    {
        printf("Connection Failed!\n");
        if(mysql_errno(conn_ptr))
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
        }
        return -2;
    }

    return 0;
}
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute)
{
    MYSQL *conn_ptr;
    MYSQL_RES *res_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    int check_num = 0;
    char sql_inq[200];
    sprintf(sql_inq,"select * from %s where %s= '%s';",TargetTable,Attribute,InquireUrl);
    printf("%s\n",sql_inq);
    conn_ptr = mysql_init(NULL);//初始化
    if(!conn_ptr)
    {
        printf("mysql_init failed!\n");
        return -1;
    }

    ret = mysql_options(conn_ptr,MYSQL_OPT_CONNECT_TIMEOUT,(const char*)&timeout);//设置超时选项
    if(ret)
    {
        printf("Options Set ERRO!\n");
    }
    conn_ptr = mysql_real_connect(conn_ptr,"localhost","root","123","books",0,NULL,0);//连接MySQL testdb数据库
    if(conn_ptr)
    {
        printf("Connection Succeed!\n");

        ret = mysql_query(conn_ptr,sql_inq); //执行SQL语句,查找大于5岁的孩子
        if(!ret)
        {
            res_ptr = mysql_store_result(conn_ptr);
            if(res_ptr)
            {
                check_num = (int)mysql_num_rows(res_ptr);
                printf("Retrieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));//在结果集合中返回行的数量
            }

            if(mysql_errno(conn_ptr))
            {
                printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
                return -2;
            }

            mysql_free_result(res_ptr);
        }
        else
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
            return -3;
        }

        mysql_close(conn_ptr);
        printf("Connection closed!\n");
    }
    else    //错误处理
    {
        printf("Connection Failed!\n");
        if(mysql_errno(conn_ptr))
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
        }
        return -2;
    }
    //printf("共有%d个结果\n",check_num);
    return check_num;
}
int MysqlDelete(char * DeleteId,char* TargetTable,char* Attribute)
{

    MYSQL *conn_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char deletewords[100];
    sprintf(deletewords,"delete from %s where %s='%s';",TargetTable,Attribute,DeleteId);
    printf("%s\n",deletewords);
    conn_ptr = mysql_init(NULL);//初始化
    if(!conn_ptr)
    {
        printf("mysql_init failed!\n");
        return -1;
    }

    ret = mysql_options(conn_ptr,MYSQL_OPT_CONNECT_TIMEOUT,(const char*)&timeout);//设置超时选项
    if(ret)
    {
        printf("Options Set ERRO!\n");
    }
    conn_ptr = mysql_real_connect(conn_ptr,"localhost","root","123","books",0,NULL,0);//连接MySQL testdb数据库
    if(conn_ptr)
    {
        printf("Connection Succeed!\n");

        ret = mysql_query(conn_ptr,deletewords); //执行SQL语句
        mysql_close(conn_ptr);
        printf("Connection closed!\n");
    }
    else    //错误处理
    {
        printf("Connection Failed!\n");
        if(mysql_errno(conn_ptr))
        {
            printf("Connect Erro:%d %s\n",mysql_errno(conn_ptr),mysql_error(conn_ptr));//返回错误代码、错误消息
        }
        return -2;
    }

    return 0;
}
int InitBooks()
{
    memset(BookInfo.BookId,0,sizeof(BookInfo.BookId));
    memset(BookInfo.BookName,0,sizeof(BookInfo.BookName));
    memset(BookInfo.BookAuthor,0,sizeof(BookInfo.BookAuthor));
    memset(BookInfo.BookWordCount,0,sizeof(BookInfo.BookWordCount));
    memset(BookInfo.Bookstatus,0,sizeof(BookInfo.Bookstatus));
    memset(BookInfo.BookUpdata,0,sizeof(BookInfo.BookUpdata));
    BookInfo.BookScore = 0;
    BookInfo.BookScoreCount = 0;
    BookInfo.OneStarRate = 0;
    BookInfo.TwoStarRate = 0;
    BookInfo.ThreeStarRate = 0;
    BookInfo.FourStarRate = 0;
    BookInfo.FiveStarRate = 0;
    memset(BookInfo.BookClass,0,sizeof(BookInfo.BookClass));
    BookInfo.AddListCount = 0;
    memset(BookInfo.BookIntro,0,sizeof(BookInfo.BookIntro));
    return 0;
}
