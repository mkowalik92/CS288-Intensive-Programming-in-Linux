#!/bin/bash

declare -a numInput

numInput=("$@")

for (( i=1; i<"${#numInput[@]}"; i++ ))
do
    j=$i
    while [ "$j" -gt "0" ] && [ "${numInput[(($j-1))]}" -gt "${numInput[$j]}" ]
    do
	temp="${numInput[$j]}"
	numInput[$j]="${numInput[(( $j-1 ))]}"
	numInput[((  j-1 ))]=$temp
	(( j-- ))
    done
done

echo "${numInput[@]}"
