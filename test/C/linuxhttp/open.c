#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
 int fd=open("file",O_WRONLY|O_CREAT,0644);
 //file文件不存在，所以在书写第二个参数时，记得把O_CREAT加上，
 //如果不加O_CREAT的话，程序就会报此文件不存在
 if(fd<0)
 {
  perror("open");
  exit(1);
 }
 const char*msg="hello file\n";
 int count=10;
 while(count--)
 {
  write(fd,msg,strlen(msg));
 }
 close(fd);
 return 0;
}
