#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "mysqlplus.h"
int MysqlDownload(char * Downloadurl,char* TargetTable)
{
    MYSQL *conn_ptr;
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char sql_down[200];
    memset(sql_down,0,sizeof(sql_down));
    sprintf(sql_down,"select * from %s limit 1",TargetTable);
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
int MysqlUpload(BlInfo* uploadBL,BInfo * uploadB,char* uploadBS,char* TargetTable,char flag)
{
    MYSQL *conn_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char sql_insert[30000];
    switch(flag)
    {
    case '1':
        printf("上传书本信息\n");
        sprintf(sql_insert, "INSERT INTO %s(BookId,BookName,BookAuthor,BookWordCount,Bookstatus,BookUpdata,BookScore,BookScoreCount,OneStarRate,TwoStarRate,ThreeStarRate,FourStarRate,FiveStarRate,BookClass,AddListCount,BookIntro) VALUES('%s','%s','%s','%s','%s','%s','%.1f','%d','%.2f','%.2f','%.2f','%.2f','%.2f','%s','%d','%s');",TargetTable, uploadB->BookId,uploadB->BookName,uploadB->BookAuthor,uploadB->BookWordCount,uploadB->Bookstatus,uploadB->BookUpdata,uploadB->BookScore,uploadB->BookScoreCount,uploadB->OneStarRate,uploadB->TwoStarRate,uploadB->ThreeStarRate,uploadB->FourStarRate,uploadB->FiveStarRate,uploadB->BookClass,uploadB->AddListCount,uploadB->BookIntro);
        break;
    case '2':
        printf("上传书单信息\n");
        sprintf(sql_insert, "INSERT INTO %s(BooklistId,BooklistName,BooklistAuthor,BooklistViews,BooklistCount,BooklistKeep,BookType,BooklistUpdata,BooklistIntro) VALUES('%s','%s','%s','%s','%d','%d','%s','%s','%s');",TargetTable, uploadBL->BooklistId,uploadBL->BooklistName,uploadBL->BooklistAuthor,uploadBL->BooklistViews,uploadBL->BooklistCount,uploadBL->BooklistKeep,uploadBL->BookType,uploadBL->BooklistUpdata,uploadBL->BooklistIntro);
        printf("%s\n",sql_insert);
        break;
    case '3':
        printf("上传id\n");
        sprintf(sql_insert,"INSERT INTO %s(BooksId) VALUES('%s');",TargetTable,uploadBS);
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
