#!/usr/bin/bash
if [[ $1 == "" ]]; then
    echo "usage: ./createfiles *number of files* "
    exit
fi

echo "creating $1 32MB testfiles"
for (( i=0; i<$1; i++ ))
do
    truncate -s 32MB "testfile_"$i
done
