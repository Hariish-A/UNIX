#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Error: Missing size argument (sz)" >&2
    exit 1
fi

sz=$1
shift

for file in "$@"; do
    if [ -f "$file" ] && [ $(stat -c%s "$file") -gt $sz ]; then
        cat "$file"
    fi
done
