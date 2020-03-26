#include<stdlib.h>
#include<stdio.h>
#include<mysql/mysql.h>

MYSQL *conn_ptr;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
unsigned int timeout = 7;   //超时时间7秒
int main()
{
    int ret = 0;
    int check_num = 0;
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

        ret = mysql_query(conn_ptr,"select * from ing where books_ing= '5e2d3c5b12b5df22a9afb1df'"); //执行SQL语句,查找大于5岁的孩子
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
    printf("共有%d个结果\n",check_num);
    return check_num;
}
