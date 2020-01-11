#!/bin/bash
i=1
tmp=0
while(($i<=100))
do
    tmp=$(($RANDOM%10 + 1))
    echo $tmp
    sleep $tmp
#    if[$tmp == 0]
#    then
#        echo $i
#    fi
    let "i++"
done
