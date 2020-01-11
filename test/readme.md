# CBooks
## 介绍
抓取优书网的网页，对数据进行处理，通过设计算法排名，找到自己想看的书
curl -L www.yousuu.com/book/175528 > test3.txt
awk '/bookId/' yousu.txt > yousu.tmp //输出包含bookId的行
echo "bookId=173807" | awk '{match($0,/bookId(.*[0-9]?)/,a);print a[1]}'
echo "bookId="173807"  repa" | awk '{match($0,/bookId=(.*)re/,a);print a[1]}'
awk '{match($0,/bookId=\"(.*)\" re/,a);print a[1]}'            //能够读取
cat yousu.txt |awk '/bookId/' |  awk '{match($0,/bookId=\"(.*)\" re/,a);print a[1]}'     //整合版本
cat awktest.awk | awk '/bookId/' |  awk '{match($0,/bookId=\"(\w+)\" r/,a);print a[1],a[2]}'
//使用\w用来限定匹配数字或者字母，从而达到非贪婪匹配的效果  
cat sedtext1.txt | LANG=C sed -r "s/[\x81-\xFE][\x40-\xFE]//g" //去除所有汉字
cat sedtext2.txt | grep -E -o "booklist(.{25})" //输出sedtext2.txt里面符合要求的字符串
