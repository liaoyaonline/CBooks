#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
typedef struct BooklistInfo
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
    char BooklistIntro[900];
} BlInfo;
int MysqlUpload(BlInfo * upload,char* TargetTable);
int MysqlDelete(char * DeleteId,char* TargetTable);
int MysqlDownload(char * Downloadurl,char* TargetTable);
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute);
int main()
{
    BlInfo T;
    BlInfo* test = &T;
    int result = 0;
    char BooklistName[100] = "2020";
    char BooklistId[100] = "5e2d3c5b12b5df22a9afb1df";
    char BooklistAuthor[100] = "likegeng";
    char BooklistViews[20] = "1.2w";
    char BooklistCount[20] = "50";
    char BooklistKeep[20] = "100";
    char BookType[400] = "A B C D E F";
    char BooklistUpdata[100] = "20200213";
    char BooklistIntro[1000] = "newsomething";
    char deleteurl[100] = "5e2d3c5b12b5df22a9afb1df";
    char Downloadurl[100];
    char Inquireurl[100] = "5e2d3c5b12b5df22a9afb1df";
    char Attribute[100] = "BooklistId";
    char TargetTable[40] = "BooklistDone";
    char TargetTabletest[40] = "ing";
    memset(Downloadurl,0,sizeof(Downloadurl));
    strcpy(test->BooklistName,BooklistName);
    strcpy(test->BooklistId,BooklistId);
    strcpy(test->BooklistAuthor,BooklistAuthor);
    strcpy(test->BooklistViews,BooklistViews);
    strcpy(test->BooklistCount,BooklistCount);
    strcpy(test->BooklistKeep,BooklistKeep);
    strcpy(test->BookType,BookType);
    strcpy(test->BooklistUpdata,BooklistUpdata);
    strcpy(test->BooklistIntro,BooklistIntro);
    //printf("%s\n %s \n %s \n %s\n",test->BooklistName,test->BooklistId,test->BooklistAuthor,test->BooklistViews);
    result = MysqlInquire(Inquireurl,TargetTable,Attribute);
    printf("查询结果是:%d\n",result);
    MysqlUpload(test,TargetTable);
    result = MysqlInquire(Inquireurl,TargetTable,Attribute);
    printf("查询结果是:%d\n",result);
    MysqlDownload(Downloadurl,TargetTable);
    printf("%s\n",Downloadurl);
    MysqlDelete(deleteurl,TargetTable);
    result = MysqlInquire(Inquireurl,TargetTable,Attribute);
    printf("查询结果是:%d\n",result);
    return 0;
}
int MysqlUpload(BlInfo * upload,char* TargetTable)
{
    MYSQL *conn_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char sql_insert[2000];
    //sprintf(sql_insert, "INSERT INTO BooklistDone(BooklistId,BooklistName,BooklistAuthor,BooklistUpdata,BooklistIntro) VALUES('%s','%s','%s','%s','%s');", BooklistId,BooklistName,BooklistAuthor,BooklistUpdata,BooklistIntro);
    sprintf(sql_insert, "INSERT INTO %s(BooklistId,BooklistName,BooklistAuthor,BooklistViews,BooklistCount,BooklistKeep,BookType,BooklistUpdata,BooklistIntro) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s');",TargetTable, upload->BooklistId,upload->BooklistName,upload->BooklistAuthor,upload->BooklistViews,upload->BooklistCount,upload->BooklistKeep,upload->BookType,upload->BooklistUpdata,upload->BooklistIntro);
    //printf("%s\n",sql_insert);
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
int MysqlDelete(char * DeleteId,char* TargetTable)
{

    MYSQL *conn_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char deletewords[100];
    char deleteurl[100] = "5e2d3c5b12b5df22a9afb1df";
    sprintf(deletewords,"delete from %s where BooklistId='%s';",TargetTable,deleteurl);
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
int MysqlDownload(char * Downloadurl,char* TargetTable)
{
    MYSQL *conn_ptr;
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    char sql_down[200];
    memset(sql_down,0,sizeof(sql_down));
    sprintf(sql_down,"select * from %s limit 0,1",TargetTable);
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

        ret = mysql_query(conn_ptr,"select * from BooklistDone limit 0,1"); //执行SQL语句
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
int MysqlInquire(char *InquireUrl,char* TargetTable,char* Attribute)
{
    MYSQL *conn_ptr;
    MYSQL_RES *res_ptr;
    unsigned int timeout = 7;   //超时时间7秒
    int ret = 0;
    int check_num = 0;
    char sql_inq[200];
    sprintf(sql_inq,"select * from %s where %s= '%s'",TargetTable,Attribute,InquireUrl);
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
