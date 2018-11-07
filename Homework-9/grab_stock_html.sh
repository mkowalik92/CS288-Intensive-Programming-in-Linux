#!/bin/bash

for ((i=0;i<=30;i++))
do
    sleep 90
    wget http://www.wsj.com/mdc/public/page/2_3021-activnyse-actives.html -O `date +"%Y_%m_%d_%H_%M_%S"`.html
    echo "Capture $i done"
done
