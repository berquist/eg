#!/usr/bin/env bash
# shellcheck disable=SC2317

set -euo pipefail

test_make() {
    make hello
    echo "?=$?"
}

test_make_subshell() {
    (make world)
    echo "?=$?"
}

always_false() {
    false
}

test_make_fail_in_makefile() {
    make explicit_fail
    echo "?=$?"
    echo "Do we get here?"  # answer: no
}

test_fail_main_shell() {
    always_false
    echo "?=$?"
}

test_fail_subshell() {
    (always_false)
    echo "?=$?"
}

# shellcheck disable=SC1090
. "$(command -v shunit2)"
