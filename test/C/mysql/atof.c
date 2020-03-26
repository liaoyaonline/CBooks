#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
   float val;
   char str[20];
   
   strcpy(str, "98993489");
   val = atof(str);
   printf("字符串值 = %s, 浮点值 = %f\n", str, val);
 
   strcpy(str, "runoob");
   val = atof(str);
   printf("字符串值 = %s, 浮点值 = %f\n", str, val);
 
   return(0);
}
