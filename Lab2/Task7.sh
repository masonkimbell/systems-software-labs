#!/bin/bash

#set fact to first parameter
#this value will hold factorial at the end
fact=$1

if [ -z $fact ]; then
	echo "error: no input parameter"
else
echo "calculating factorial of "$fact
fi

#will start at (input - 1) and will decrease by 1 each iteration
let dec="$fact - 1"
#echo $dec

while [ "$dec" -gt 1 ]; do
	let fact="$fact * $dec"
	let dec--
	#echo "dec is currently "$dec
done

echo "factorial of "$1" is "$fact

exit 0
