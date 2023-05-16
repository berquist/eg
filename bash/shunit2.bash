#!/usr/bin/env bash

set -euo pipefail

SHUNIT_COLOR=none

test_make() {
    make hello
    echo $?
}

test_make_subshell() {
    (make world)
    echo $?
}

. /usr/bin/shunit2
