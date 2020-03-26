#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;

  char str[1024*1024];
  char *p = NULL;
  memset(str,0,sizeof(str));
  int n = 0;
  int count = 0;
  int fd=open("file",O_WRONLY|O_CREAT,0644);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.yousuu.com/booklist/5a405904da8315b47e51cbb6");
    //res = curl_easy_perform(curl);

    if(CURLE_OK == res) {
      char *ct;
      /* ask for the content-type */
      //res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

      if((CURLE_OK == res) && ct)
      {
          //printf("We received Content-Type: %s\n", ct);
          //while((n = write(fd,ct+count,1024)) != 0)
          //{
          //    count += n;
          //}
      }
    }
    close(fd);
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
