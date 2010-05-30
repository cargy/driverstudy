#!/bin/bash
count=0
total=`ls img/*.jpg | wc -l`
files="ls img/*.jpg"
for i in $( ls img/*.jpg ); do
    NAME=${i%.jpg}
    EXT=${i##*.}
    BASENAME=${i##*/}
    BASENAME=${BASENAME%.*}
    #TYPE=`soxi -t "$i"`
    TYPE=$EXT 
    let count=count+1
    echo Converting file: $count/$total $i \($TYPE\) to imgpng/$BASENAME.png
    convert -quality 99 $i imgpng/$BASENAME.png     
done

echo Files proccessed: $count
