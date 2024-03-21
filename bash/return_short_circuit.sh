#!/bin/bash

set -x
set -o pipefail

retval=0
true || retval=$?
echo "retval=${retval}"

retval=0
x=4 || retval=$?
echo "retval=${retval}"

myfunc_true() {
    local ret=0
    true || ret=$?
    return $ret
}

myfunc_assign() {
    local ret=0
    y=23 || ret=$?
    return $ret
}

myfunc_true
echo $?
myfunc_assign
echo $?
