#!/bin/bash
# shellcheck disable=SC2128
# Expanding an array without an index only gives the first element.

# Example showing how FUNCNAME
# (https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html)
# works.

inner2() {
    echo "first bad: ${FUNCNAME}"
    echo "all: ${FUNCNAME[*]}"
}

inner() {
    echo "first bad: ${FUNCNAME}"
    inner2
    echo "all: ${FUNCNAME[*]}"
}

run() {
    echo "first bad: ${FUNCNAME}"
    echo "first good: ${FUNCNAME[0]}"
    echo "all: ${FUNCNAME[*]}"
    inner
    echo "first bad: ${FUNCNAME}"
    echo "first good: ${FUNCNAME[0]}"
    echo "all: ${FUNCNAME[*]}"
}

run
