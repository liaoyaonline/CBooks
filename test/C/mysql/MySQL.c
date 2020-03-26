#include<stdlib.h>
#include<stdio.h>
#include<mysql/mysql.h>

MYSQL *conn_ptr;
unsigned int timeout = 7;   //超时时间7秒
int main()
{
    int ret = 0;
    char sql_insert[2000];
    char BooklistName[100] = "2020";
    char BooklistId[100] = "5e2d3c5b12b5df22a9afb1df";
    char BooklistAuthor[100] = "likegeng";
    char BooklistUpdata[100] = "20200213";
    char BooklistIntro[1000] = "newsomething";
    sprintf(sql_insert, "INSERT INTO BooklistDone(BooklistId,BooklistName,BooklistAuthor,BooklistUpdata,BooklistIntro) VALUES('%s','%s','%s','%s','%s');", BooklistId,BooklistName,BooklistAuthor,BooklistUpdata,BooklistIntro);
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
