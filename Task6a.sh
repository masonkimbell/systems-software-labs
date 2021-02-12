#!/bin/bash

for i in $(seq 1 5); do
	for j in $(seq 1 $i); do
		printf "%c$i"
	done
	printf "\n"
done

exit 0;
