#include <stdio.h>
 
int main (int argc,char** argv)
{
   /* 局部变量定义 */
 
    char flag = '1';
   switch(flag)
   {
   case '1' :
      printf("读取书单内书号\n" );
      break;
   case '2' :
      printf("读取书单名称\n");
      break;
   case '3' :
      printf("读取书单作者\n" );
      break;
   case '4' :
      printf("读取书单基本信息\n" );
      break;
   case '5' :
      printf("读取书单类型\n" );
      break;
   case '6':
      printf("读取书单介绍\n");
      break;
   default :
      printf("无效的flag,不能读取\n" );
   }
   return 0;
}
