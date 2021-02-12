#!/bin/bash

#returns true if num is between 5 and 9
between(){
	if [ "$1" -ge 5 ]; then
		if [ "$1" -le 9 ]; then
			betweenCheck=0
		fi
	fi
}

betweenCheck=999

echo "Enter a number between 5 and 9"
read num
between "$num"

while [ "$betweenCheck" -ne 0 ]; do
	echo "Number is not within range. Enter another."
	read num
	between "$num"
done

for i in $(seq 1 $num); do
	let spaceCount="$num - $i"
	for k in $(seq 1 $spaceCount); do
		printf " "
	done

	for j in $(seq 1 $i); do
		printf "%c $i"
	done
	printf "\n"
done

exit 0
