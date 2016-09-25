#!/bin/bash

# Bash script that takes two arguments
# and prints floating point numbers one per line
# the First is the maximum positive value
# the Second is the number of lines to output
#

# MAX POS

MAXPOS=$1;
if [ -z $MAXPOS ];
then
    MAXPOS=50;
fi

DBPOS=$((${MAXPOS}*2));

LINES=$2;
if [ -z $LINES ];
then
    LINES=1000;
fi

for i in $(seq 1 $LINES);
do
    SOMENUM=$(($RANDOM%${DBPOS}));
    if [[ $SOMENUM -gt ${MAXPOS} ]]; then
	SOMENUM=$((${SOMENUM} - ${DBPOS}))
    fi
    FRACTPT=$((${RANDOM}%9999))
    echo ${SOMENUM}.${FRACTPT}
done
