# 关于feof机制的详解
## 遇到的问题
在撸代码的时候遇到一个问题，使用feof(fp)做为文件结束检测，使用fscanf读取文件，但是往往会
读取最后一行两次。
测试文档如下:
测试代码如下：
```
#include <stdio.h>
#include <string.h>
int main()
{
    char StrTmp[80];
    memset(StrTmp,0,sizeof(StrTmp));
    FILE *fp;
    fp=fopen("test.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",StrTmp);
        printf("%s\n\n",StrTmp);
    }
    fclose(fp);
    return 0;
}
```
测试结果如下：

从结果上来看，test４输出了两次，然而我只需要输出一次。
## 详解
查询feof命令原型
```
man feof
```
结果如下：
由此我们知道feof的函数原型
```
int feof(FILE *stream);
```
feof的作用

- The function feof() tests the  end-of-file  indicator  for  the  stream pointed  to by stream, returning nonzero if it is set.  The end-of-file indicator can be cleared only by the function clearerr().

feof会检测文件指针是否到达文件末尾,如果到了，返回一个非零值。

注意：feof函数读取文件最后一个字符的时候依然会返回0,表明没有到达文件结尾，只有再往后读取字符(越过最后一个字符)，feof()才会返回一个非零值，表示到达文件结尾。
测试代码
```
#include <stdio.h>
#include <string.h>
int main()
{
    char StrTmp[80];
    memset(StrTmp,0,sizeof(StrTmp));
    FILE *fp;
    fp=fopen("test.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",StrTmp);
        if(feof(fp))
        {
            break;
        }
        printf("%s\n\n",StrTmp);
    }
    fclose(fp);
    return 0;
}
```
执行结果
能够正常执行。
