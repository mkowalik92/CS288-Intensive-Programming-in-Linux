#!/bin/bash

declare -a dirContent

function reverse()
{
    local temp tempGoTo x=$((${#dirContent[@]} / 2))
    for (( j=0; j<x; j++ ))
    do
	temp="${dirContent[$j]}"
	tempGoTo=$((${#dirContent[@]}-(j+1)))
	dirContent[$j]="${dirContent[$tempGoTo]}"
	dirContent[$tempGoTo]="$temp"
    done
}

function main()
{
    cd "$1"
    for i in *
    do
	dirContent+=("$i")
    done
    reverse
}


main "$1"
echo ${dirContent[@]}
