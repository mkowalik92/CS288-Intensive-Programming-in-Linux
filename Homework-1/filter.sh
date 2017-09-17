#!/bin/bash

function filter()
{
    for j in *
    do
	local fileSize
	fileSize=$(stat -c%s "$j")
	if [ "$fileSize" -gt "$averageSize" ]
	then
	    filteredFiles+=("$j")
	fi
    done
}

function average()
{
    local sum=0
    local count=0
    for i in *
    do
	(( sum += $(stat -c%s "$i") ))
	(( count++ ))
    done
    averageSize=$(( sum / count ))
}

function main()
{
    cd "$1"
    average "$1"
    declare -a filteredFiles
    filter "$1"
    echo "${filteredFiles[@]}"
}

main "$1"
