#!/usr/bin/env bash

IFS=$'\n'
file_array=( `ls -lS $1 | grep -v "^d" | awk '{print $9,$5}'` )
nb_array=${#file_array[@]}

printf "\nFile name | File size\n"
# for index in ${!file_array[*]}
# do
for (( i=0; i < $nb_array; i++ )); do
    printf "%-8d %s\n" "${nb_array[$i]}" "${file_array[$i]}"
done
