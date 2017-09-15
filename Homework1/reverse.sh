#!/bin/bash

function reverse() {
    local temp tempGoTo x=$((${#dirContent[@]} / 2))
    local y=${x%.*}
    
    for (( i=0; i<y; i++ ))
    do
	temp=${dirContent[$i]}
	#tempGoTo=`expr ${#dirContent[@]} - '(' $i + 1 ')'`
	tempGoTo=$((${#dirContent[@]}-(i+1)))
        #echo $temp is going to $tempGoTo
	dirContent[$i]=${dirContent[$tempGoTo]}
	#echo ${dirContent[$i]} was sent to $i
	dirContent[$tempGoTo]=$temp
    done
    echo output:  "${dirContent[@]}"
}

function main() {
    declare -a dirContent
    for x in /$1/*
    do
	dirContent+=("${x##*/}")
    done
    echo input:  "${dirContent[@]}"
    reverse
    #$dirContent
}

main "$1"

