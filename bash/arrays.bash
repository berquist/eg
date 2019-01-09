#!/usr/bin/env bash

set -eu

# test_sets="analysis1 dev1 eval1 eval2"

# for test in $test_sets; do
#     scoring_opts=""
#     if [[ $test == "dev1" || $test == "eval1" || $test == "eval2" ]]; then
#         scoring_opts="--skip-scoring true"
#     fi
#     echo "$test: $scoring_opts"
# done

declare -A test_sets=([analysis1]=0 [dev1]=1 [eval1]=1 [eval2]=1)
echo "keys: ${!test_sets[@]}"
echo "values: ${test_sets[@]}"

for test_set in "${!test_sets[@]}"; do
    scoring_opts=""
    if [[ "${test_sets[$test_set]}" == 1 ]]; then
        scoring_opts="--skip-scoring true"
    fi
    echo "$test_set: $scoring_opts"
done
