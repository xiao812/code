#!/bin/bash
if [ $# -ne 1 ]; then 
    echo "usage ./transform.sh <filename>"
    exit 
fi
`od -v -An -txC $1 | awk -f transform.awk > result2`
`xxd -r -p result2 > result.rbf`
`rm result2`
