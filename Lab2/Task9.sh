#!/bin/bash

#start from home directory
cd

echo "enter a directory to search for a file"
echo "enter full path to search"
echo "ex: if you want to search ~/Documents/COSC350, enter Documents/COSC350"
read dir

if [ -d $dir ]; then
cd $dir
attemptCount=1
	while [ "$attemptCount" -le 3 ]; do
		echo "enter the name of a file in the directory to search for"
		read fname
		if [ -e $fname ]; then
			if [ -r $fname ]; then
				echo "file exists and is readable"
				break
			else
				echo "error: the file is not readable"
				if [ "$attemptCount" -lt 3 ]; then
					echo "attempt #"$attemptCount
					let attemptCount++
				else
					echo "error: file is not readable after 3 incorrect attempts"
					exit 3
				fi
			fi
		else
			echo "error: the file does not exist"
			if [ "$attemptCount" -lt 3 ]; then
				echo "attempt #"$attemptCount
				let attemptCount++
			else
				echo "error: file does not exist after 3 incorrect attempts"
				exit 2
			fi
		fi
	done

echo "enter a word to search for"
read word

if grep -q $word $fname; then
	echo $word" FOUND!"
else
	echo $word" NOT FOUND!"
	exit 4
fi

echo "success"
exit 0

else
	echo "error: the directory does not exist"
exit 1
fi

exit 0
