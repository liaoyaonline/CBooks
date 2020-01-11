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
    #cat ing.txt
    offset_address=$(sed -n 1p ing.txt)
    #echo $offset_address
    FILENAME_TMP=$(cat ing.txt | sed -n 1p | awk -F"/" '{print $2}')
    #echo $FILENAME_TMP
    FILENAME=$FILENAME_TMP".txt"
    #echo $FILENAME
    sed -i '1d' ing.txt
    #cat ing.txt
    ab_address=$address$offset_address
    #echo $ab_address
    AB_FILENAME=$TMP_FILE$FILENAME
    #echo $AB_FILENAME
    curl -L $ab_address > $FILENAME
    cp $FILENAME $AB_FILENAME
    echo $AB_FILENAME
    echo $FILENAME
}
parse(){
    NUM=$(cat $FILENAME | grep -E -o "data-v-6581533a>[0-9]{1,5}<" | awk -F "[><]" '{print $2}')
    RESULT=$FILENAME_TMP" "$NUM
    echo $RESULT >> result.txt
    cat $FILENAME | grep -E -o "book/[0-9]{1,6}" | uniq >> ing.txt
    cat $FILENAME | grep -E -o "booklist/[a-z0-9]{24}" >> ing.txt
    echo $offset_address >> done.txt
    rm $FILENAME
}
main(){
    int=1
    tmp=0
    while(($int<=100))
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
