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
    #删除文本ing.txt第一行
    sed -i '1d' ing.txt
    #将address和offset_address组合成url
    ab_address=$address$offset_address
    #将TMP_FILE和FILENAME组合成文件绝对地址
    AB_FILENAME=$TMP_FILE$FILENAME
    #抓取网页并将其保存到文件
    curl -L $ab_address > $FILENAME
    #将文件复制到文件绝对地址
    cp $FILENAME $AB_FILENAME
}
parse(){
    #将网页中的书有多少个书单的数字提取出来
    NUM=$(cat $FILENAME | grep -E -o "data-v-6581533a>[0-9]{1,5}<" | awk -F "[><]" '{print $2}')
    #将书号 书单数拼接起来
    RESULT=$FILENAME_TMP" "$NUM
    #将RESULT加入文本后边
    echo $RESULT >> result.txt
    #将网页中爬取的书号和书单号加入待爬取int.txt
    cat $FILENAME | grep -E -o "book/[0-9]{1,6}" | uniq >> ing.txt
    cat $FILENAME | grep -E -o "booklist/[a-z0-9]{24}" >> ing.txt
    #将已经爬取书号和书单号加入已爬取
    echo $offset_address >> done.txt
    #删除临时文件
    rm $FILENAME
}
main(){
    int=1
    tmp=0
    while(($int<=1000))
    do
        tmp=$(($RANDOM%60 + 1))
        echo "这是第 $int 次爬取，这一次休眠 $tmp s"
        sleep $tmp
        get
        parse
        let "int++"
    done
}
main
