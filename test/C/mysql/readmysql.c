#include<stdlib.h>
#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>
MYSQL *conn_ptr;
MYSQL_RES *res;
MYSQL_ROW row;
unsigned int timeout = 7;   //超时时间7秒
int main()
{
    int ret = 0;
    char downloadurl[200];
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
            printf("%s\n",row[2]);
            printf("%s\n",row[1]);
            sprintf(downloadurl,"%s",row[0]);
        }
        //sprintf(downloadurl,"%s",row[0].BooklistId);
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
    printf("%s\n",downloadurl);
    return 0;
}
