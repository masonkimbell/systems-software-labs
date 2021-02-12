#!/bin/bash

echo "note: all invalid characters in first parameter will be ignored"

if [ "$#" -ne 1  ]; then
echo "invalid number of parameters"
exit 0
fi

param=$1
echo "you entered "$param
len=0
len=`expr length $param`
#echo "the length of "$param" is "$len

sum=0

for i in $(seq 1 $len); do
	value=`expr substr $param $i 1`
	let sum="$sum + $value"
done

echo "the sum of the digits of "$param" is "$sum

exit 0
