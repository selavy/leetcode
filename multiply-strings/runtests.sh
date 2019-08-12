#!/bin/sh

BIN=$1

for f in ./tests/input*.txt;
do
    ($1 $f && echo "Passed.") || exit 1
done
