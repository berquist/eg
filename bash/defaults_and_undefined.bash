#!/bin/bash

_MOCK_HASH_DEVEL="25c27ad3f3da0013e5aa2b7ee407cf075e1b3645"
_MOCK_HASH_MASTER="25c27ad3f3da0013e5aa2b7ee407cf075e1b36aa"
_MOCK_HASH_MACRO="macrohash"

branch_to_commit_hash() {
    # This is a mock implementation.
    # The real one does $(git log -n 1 "${branch}" | grep commit | cut -d ' ' -f 2)
    local branch="${1}"
    if [[ "${branch}" == "devel" ]]; then
        echo "${_MOCK_HASH_DEVEL}"
    elif [[ "${branch}" == "master" ]]; then
        echo "${_MOCK_HASH_MASTER}"
    elif [[ "${branch}" == "macrobranch" ]]; then
        echo "${_MOCK_HASH_MACRO}"
    else
        exit 1
    fi
}


get_commit_hash() {
    # A default branch *must* be specified.
    # The commit hash and specific branch are optional.

    # non-zero length?
    # branch no hash no -> default branch to hash
    # branch no hash yes -> use hash as-is
    # branch yes hash no -> specific branch to hash
    # branch yes hash yes -> return 1

    local branch_specified="${1}"
    local branch_default="${2}"
    local hash="${3}"

    if [[ -z "${branch_default}" ]]; then
        echo "No default branch specified as fallback"
        return 1
    fi

    if [[ -z "${branch_specified}" ]] && [[ -z "${hash}" ]]; then
        ret="$(branch_to_commit_hash "${branch_default}")"
        echo "${ret}"
    elif [[ -z "${branch_specified}" ]] && [[ -n "${hash}" ]]; then
        echo "${hash}"
    elif [[ -n "${branch_specified}" ]] && [[ -z "${hash}" ]]; then
        ret="$(branch_to_commit_hash "${branch_specified}")"
        echo "${ret}"
    else
        echo "Cannot pick between both non-default branch and specified commit hash"
        return 1
    fi
}

# This naive attempt doesn't work
#
# set_commit_hash() {
#     local repo_name="${1}"

#     local varname_branch="SST_${repo_name}BRANCH"
#     local varname_branch_default="SST_${repo_name}BRANCH_default"
#     local varname_hash="SST_${repo_name}_HASH"

#     local commit_hash
#     commit_hash=$(get_commit_hash "${!varname_branch}" "${!varname_branch_default}" "${!varname_hash}")

#     # Now that the commit hash is determined, unconditionally set its
#     # respective variable and remove any possibility of reading the branch
#     # variable later on.
#     eval "${!varname_hash}=${commit_hash}"
#     eval "unset ${!varname_branch}"
# }

# ret="$(branch_to_commit_hash "master")"
# echo "${ret}"
# ret="$(branch_to_commit_hash "devel")"
# echo "${ret}"
# ret="$(get_commit_hash "${SST_JUNOBRANCH}" "${SST_JUNOBRANCH_default}" "${SST_JUNO_HASH}")"
# echo "${ret}"
