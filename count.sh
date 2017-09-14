#!/bin/bash

declare -A binCountArray

for y in /bin/[A-Za-z]*;
do
    comNoBin=${y:5:1}
    #comNoBin=`echo ${y:5:1} | tr ':upper:' 'lower'`
    if ! [[ "$comNoBin" =~ [^A-Z] ]]; then
	#
	#echo ":Uppercase `echo $comNoBin | tr '[:upper:]' '[:lower:]'` detected:"
	comNoBinLower=`echo $comNoBin | tr '[:upper:]' '[:lower:]'`
	let binCountArray[$comNoBinLower]+=1
    else
	let binCountArray[$comNoBin]+=1
    fi
done

for letter in {a..z};
do
    echo $letter " " ${binCountArray[$letter]}
done
