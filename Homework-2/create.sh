#!/bin/bash

function depthFirst()
{
    if [ "$1" -gt "0" ]
    then
	local x=0
	for (( ; x<"$2"; x++ ))
	do
	    echo "$3"/"$x"
	    #mkdir "$x"/"$b"
	    depthFirst $(( $1 - 1 )) "$2" "$3"/"$x"
	done
    fi
}

function breadthFirst()
{
    local depth="$1" breadth="$2" dirName="$3"
    open=( "$dirName" )
    closed=()
    for (( d=0; d<"$depth"; d++ ))
    do
	tempopen=()
	for x in "${open[@]}"
	do
	    temp=()
	    for (( b=0; b<"$breadth"; b++ ))
	    do
		temp=( "${temp[@]}" "$x"/"$b" )
		echo "$x"/"$b"
		#mkdir "$x"/"$b"
	    done
	    closed=( "${closed[@]}" "$x" )
	    tempopen=( "${tempopen[@]}" "${temp[@]}" )
	done
	open=( "${tempopen[@]}" )
    done
}

function main()
{
    local depth="$1" breadth="$2" dirName="$3" treeType="$4"
    if [[ "$treeType" == "breadth" ]]
    then
	breadthFirst "$depth" "$breadth" "$dirName"
    fi
    if [[ "$treeType" == "depth" ]]
    then
	depthFirst "$depth" "$breadth" "$dirName"
    fi
}

main "$1" "$2" "$3" "$4"
