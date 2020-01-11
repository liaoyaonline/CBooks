#!/bin/bash
a=$(sed -n 1p ing.txt)
#b=$(sed -n '1!P;N;$q;D' $1 | awk -F"," '{print $1}')
echo $a
#echo $b
