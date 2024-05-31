#!/bin/bash

set -eo pipefail
set -x

args_file="${1}"

converted_line=""
if [ -f "${args_file}" ]; then
    readarray -t args_lines < "${args_file}"
    for arg_line in "${args_lines[@]}"; do
        if [[ ${arg_line} != \#* ]]; then
            formatted_arg="$(printf -- '--build-arg=\"%s\"' "${arg_line}")"
            converted_line="${converted_line} ${formatted_arg}"
        fi
    done
fi

cmd="podman build --no-cache ${converted_line[*]} -t myimage ."
eval "${cmd}"
