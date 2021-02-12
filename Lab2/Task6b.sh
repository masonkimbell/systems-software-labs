#!/bin/bash

for i in $(seq 1 5); do
	for j in $(seq 1 $i); do
		printf "*"
	done
	printf "\n"
done

for i in $(seq 1 4); do
	j=`expr 4 - $i + 1`
	while [ "$j" -ne 0 ]; do
		printf "*"
		let j--
	done
	printf "\n"
done

exit 0
