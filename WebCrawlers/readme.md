# 小说爬虫
## 爬虫流程介绍
这里是爬取数据的源代码
其流程如下：
1，从mysql数据中的ing表中获取一个网址，爬取该网址。
2，将该网址进行解析，提取出需要的内容，比如说该网址是书单，提取出该书单本身信息，存入mysql中
的BooklistDone表内。提取出书单里面的书本号，假如该书本号既不在ing表内，也不在BookDone表内，将该书号
存入ing中做为后续爬取网址。
## 代码更新记录
重构以下几个部分

- 函数命名
- 将函数实现部分移动到自定义头文件中，源代码行数不能超过100
- 建立Makefile文件
拓展项
- 编写配置文档，程序从配置文档中读取包括数据库名，用户名和密码等信息
- 编写命令行参数函数，根据不同的参数执行不同的功能。
- 高内聚，低耦合，对函数进行优化，最好一个函数只完成一个功能。
## 文件用途介绍
```
├── bin  //保存可执行文件的文件夹
│   └── regexbook   //可执行文件
├── include  //保存头文件的文件夹
│   ├── mysqlplus //保存对mysql进行操作的函数实现
│   └── mysqlplus.h//对mysql进行操作的函数定义
├── Makefile  //将代码编译成可执行文件的Makefile文件
├── readme.md  //对本项目的一些介绍
└── src  //保存源代码的文件夹
    └── regexbook4.c//源代码

```
## 安装与使用
* 安装环境
需要确定是否已经安装了mysql和curl
安装`mysql`命令
```
sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev
```
安装`curl`命令
```
sudo apt-get install curl
sudo apt-get install libcurl4-openssl-dev
```
* 安装软件
```
git clone 
cd CBooks
make
make clean
```

* 使用软件
```
cd bin
./regexbooks
```
