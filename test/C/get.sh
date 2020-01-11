#!/bin/bash
TMP_FILE="/home/liaoya/github/CBooks/test/result/"
address="www.yousuu.com/"
offset_address=""
ab_address=""
FILENAME_TMP=""
FILENAME=""
AB_FILENAME=""
NUM=""
RESULT=""
get(){
    #读取ing.txt第一行将它赋值给offset_address
    offset_address=$(sed -n 1p ing.txt)
    #将ing.txt中第一行的书号提取出来赋值给FILENAME_TMP
    FILENAME_TMP=$(cat ing.txt | sed -n 1p | awk -F"/" '{print $2}')
    #将书号加txt变为备用的文件名
    FILENAME=$FILENAME_TMP".txt"
    #将address和offset_address组合成url
    ab_address=$address$offset_address
    #将TMP_FILE和FILENAME组合成文件绝对地址
    AB_FILENAME=$TMP_FILE$FILENAME
    #抓取网页并将其保存到文件
    curl -L $ab_address > $FILENAME
    #将文件复制到文件绝对地址
    cp $FILENAME $AB_FILENAME
}
get
