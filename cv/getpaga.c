#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>

#define MAX_URL_LEN 1024
#define MAX_FILE_NAME_LEN 64
#define MAX_REUQEST_LEN 1024
#define BUFF_MAX_SIZE 512
#define PAGE_MAX_SIZE 4096*128
void parseURL(char * url,char* host,char* path)
{    
    //char tmp[MAX_URL_LEN] = {0};
    char*ptmp = NULL;
    strcpy(host,url);
    if((ptmp = strstr(url,"http://")) != NULL)//https format
    {
        ptmp = ptmp + 7;
        strcpy(host,ptmp);
    }else if(ptmp = NULL,(ptmp = strstr(url,"https://")) != NULL)//http format
    {    
        ptmp = ptmp + 8;
        strcpy(host,ptmp);
    }
    ptmp = NULL;
    if((ptmp = strpbrk(host,"/")) != NULL)
    {
        strcpy(path,ptmp);
        ptmp[0] = '\0';
    }

}
void getPage(char* host,char* path,char* file)
{    
    struct hostent *phost;
    if(0 == (phost = gethostbyname(host)))
    {
        printf("host err\n");
        exit(1);
    }

    struct sockaddr_in pin;
    int port = 80;
    bzero(&pin,sizeof(pin));
    pin.sin_family=AF_INET;
    pin.sin_port=htons(port);
    pin.sin_addr.s_addr=((struct in_addr*)(phost->h_addr))->s_addr;
    int isock;
    if((isock = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("socket err\n");
        exit(1);
    }
    char requestHeader[MAX_REUQEST_LEN] = "GET ";
    strcat(requestHeader,path);
    strcat(requestHeader," HTTP/1.0\r\nHost: ");
    strcat(requestHeader,host);
    strcat(requestHeader,"\r\nAccept: */*\r\n");
    strcat(requestHeader,"User-Agent: Mozilla/4.0(compatible)\r\n");
    strcat(requestHeader,"Connection: Keep-Alive\r\n");
    strcat(requestHeader,"\r\n");
    
    if(connect(isock,(struct sockaddr*)&pin,sizeof(pin)) == -1)
    {
        printf("connect err\n");
        exit(1);
    }

    if(send(isock,requestHeader,strlen(requestHeader),0) == -1)
    {
        printf("send err\n");
        exit(1);
    }
    //struct timeval timeout={1,0}; 
    //setsockopt(isock,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
    char buffer[BUFF_MAX_SIZE];
    char page[PAGE_MAX_SIZE];
    int len;
    printf("Start fetch\n");
    int fd = open("file",O_RDWR|O_CREAT,0666);
    int flag = 0;
    char tmpch;
    //while(recv(isock,&tmpch,sizeof(char))>0)
    //{    
    //    if(tmpch == '\r')
    //    {
    //       如何读到一个http请求头的末尾？//        http://www.runoob.com/http/http-messages.html
    //    }
    //}
    while((len = recv(isock,buffer,BUFF_MAX_SIZE-1,0))>0)
    {
        buffer[len]='\0';
            
        write(fd,buffer,strlen(buffer)+1);

    }
    close(isock);
    close(fd);
}

int main()
{
    char url[MAX_URL_LEN] = "http://www.runoob.com/http/http-intro.html";
    //char url[MAX_URL_LEN] = "https://www.runoob.com/http/http-intro.html";
    char host[MAX_URL_LEN] = {0};
    char path[MAX_URL_LEN] = {0};
    char file[MAX_FILE_NAME_LEN]  = "file";
    
    //parse url to get host and page path
    parseURL(url,host,path);
    //puts(host);
    //puts(path);
    //connect and sv the page into a file
    getPage(host,path,file);
    
}
