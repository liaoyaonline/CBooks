#!/bin/bash
TMP_FILE="/home/liaoya/github/CBooks/cvtest1.txt"
word=$2
option=$1
get(){
    keyword=$1
    curl -L 'www.yousuu.com/book/172254/' | awk 'BEGIN{i=0;j=0;}{while(/href=/){print $0}}' > $TMP_FILE
}
get
