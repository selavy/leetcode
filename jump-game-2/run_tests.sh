#!/usr/bin/env bash

set -e

function die()
{
    echo $1
    exit 1
}

ninja -C build || die "Failed to compile"
for f in ./input*.txt;
do
    echo ""
    echo ""
    echo "Running ${f}..."
    ./build/jump $f
done;
