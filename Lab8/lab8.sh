#!/bin/bash

###########################
# PART 1
###########################
#sum=0
#avg=0
#count=$#

# ERROR FOR INVALID ARG #
#if [ $count -lt 1 ]; then
#	echo "ERROR: Must have at least one argument!"
#	exit 1
#elif [ $count -gt 7 ]; then
#	echo "ERROR: Must have less than seven arguments!"
#	exit 1
#fi

# SUM OF COMMAND LINE VALUES #
#for i do
#	sum=$(expr $sum + $i)
#done
#echo "Sum of values    : $sum"

# AVG OF COMMAND LINE VALUES #
#avg=$(expr $sum / $count)
#echo "Average of values: $avg"


##########################
# PART 2 & 3
##########################
declare -a arr
sum=0
avg=0

# LOAD VALUES TO ARRAY #
echo "Please input values seperated by line:"
echo "Press Ctrl-D to stop entering values."
echo

while read -r n; 
do
	arr+=( $n )
done

# ERROR FOR INVALID ARG #
count=${#arr[@]}
if [ $count -lt 1 ]; then
	echo "ERROR: Must be at least one argument!"
	exit 1
elif [ $count -gt 7 ]; then
	echo "ERROR: Must be less than seven arguments!"
	exit 1
fi

# SUM OF ELEMENTS & MAX ELEMENT #
max=${arr[0]}
for i in ${arr[@]}
do
	sum=$(expr $sum + $i )
	if [ $i -gt $max ]; then
		max=$i
	fi
done

# AVG OF ELEMENTS #
avg=$(expr $sum / $count )

echo
echo "Elements in Array  : ${arr[*]}"
echo "Sum of elements    : $sum"
echo "Average of elements: $avg"
echo "Maximum element    : $max"
