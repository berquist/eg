#!/usr/bin/env bats
# -*- mode: shell-script; -*-

source ./defaults_and_undefined.bash

setup() {
    # not loaded transitively!
    load '/usr/lib/bats-support/load.bash'
    load '/usr/lib/bats-assert/load.bash'
}

SST_COREBRANCH_default=devel
SST_MACROBRANCH_default=devel
SST_JUNOBRANCH_default=master
SST_EXTERNALELEMENTBRANCH_default=master
SST_CORE_HASH="f12ba9266204f841b5eff7a74116707d228cb008"
SST_MACROBRANCH="macrobranch"
SST_EXTERNALELEMENTBRANCH="externalelementbranch"
SST_EXTERNALELEMENT_HASH="externalelementhash"

# These branch_to_commit tests aren't good tests but still serve as bats examples.
@test "branch_to_commit_hash_devel" {
    run branch_to_commit_hash "devel"
    assert_output "${_MOCK_HASH_DEVEL}"
}

@test "branch_to_commit_hash_master" {
    run branch_to_commit_hash "master"
    assert_output "${_MOCK_HASH_MASTER}"
}

@test "get_commit_hash_no_default_branch" {
    run get_commit_hash "${SST_ELEMENTSBRANCH}" "${SST_ELEMENTSBRANCH_default}" "${SST_ELEMENTS_HASH}"
    assert_failure
    assert_output "No default branch specified as fallback"
}

@test "get_commit_hash_branch_no_hash_no" {
    run get_commit_hash "${SST_JUNOBRANCH}" "${SST_JUNOBRANCH_default}" "${SST_JUNO_HASH}"
    assert_success
    assert_output "${_MOCK_HASH_MASTER}"
}

@test "get_commit_hash_branch_no_hash_yes" {
    run get_commit_hash "${SST_COREBRANCH}" "${SST_COREBRANCH_default}" "${SST_CORE_HASH}"
    assert_success
    assert_output "${SST_CORE_HASH}"
}

@test "get_commit_hash_branch_yes_hash_no" {
    run get_commit_hash "${SST_MACROBRANCH}" "${SST_MACROBRANCH_default}" "${SST_MACRO_HASH}"
    assert_success
    assert_output "${_MOCK_HASH_MACRO}"
}

@test "get_commit_hash_branch_yes_hash_yes" {
    run get_commit_hash "${SST_EXTERNALELEMENTBRANCH}" "${SST_EXTERNALELEMENTBRANCH_default}" "${SST_EXTERNALELEMENT_HASH}"
    assert_failure
    assert_output "Cannot pick between both non-default branch and specified commit hash"
}
