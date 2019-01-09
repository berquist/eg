#!/usr/bin/env bash

for i in {31..120}; do
    line="tdnnf-layer name=tdnnf${i} \$tdnnf_opts dim=\$dim bottleneck-dim=\$bndim time-stride=3"
    echo $line
done
