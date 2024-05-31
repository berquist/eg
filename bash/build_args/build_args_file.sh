#!/bin/bash

set -eo pipefail
set -x

args_file="${1}"

converted_line=""
if [ -f "${args_file}" ]; then
    readarray -t args_lines < "${args_file}"
    for arg_line in "${args_lines[@]}"; do
        converted_line="${converted_line} $(printf -- "--build-arg=%s" ${arg_line})"
        echo ${arg_line[0]}
    done
    #echo "${converted_line[@]}"
fi

#echo "podman build ${converted_line[*]} -t myimage ."
# shellcheck disable=SC2086,SC2048
#podman build --no-cache ${converted_line[*]} -t myimage .
