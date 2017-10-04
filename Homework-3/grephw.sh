#!/bin/bash

wget -O index.html www.youtube.com

touch views.txt duration.txt user.txt title.txt id.txt

count=0

grep views index.html |
    while read line
    do
	views=`expr "$line" : ".*<li>\(.*\) views</li>"`
	#echo "${views//,/}"
	echo "${views//,/}" >> views.txt
    done

grep Duration index.html |
    while read line
    do
	duration=`expr "$line" : ".*Duration: \(.*\).</span></h3>"`
	#echo "$duration"
	echo "$duration" >> duration.txt
    done

grep views index.html |
    while read line
    do
	user=`expr "$line" : ".*data-sessionlink=\"itct=.*\" >\(.*\)</a>.*"`
	#echo "$user"
	echo "$user" >> user.txt
    done

grep href index.html |
    while read line
    do
	id=`expr "$line" : ".*<a href=\"/\(.*\)\" class=\"g-hovercard"`
	if [ -z "$id" ]
	then
	    continue
	fi
	newId=`expr "$id" : "[a-z]*/\(.*\)"`
	#echo "$newId"
	echo "$newId" >> id.txt
    done

grep views index.html |
    while read line
    do
	title=`expr "$line" : ".*title=\"\(.*\)\" aria-described.*"`
	#echo "${title//,/&#44;}"
	echo "${title//,/&#44}" >> title.txt
    done

paste -d"," views.txt duration.txt user.txt title.txt id.txt > tbl.csv
